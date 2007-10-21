/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2007 OpenSWG Team <http://www.openswg.com>
 */

// *********************************************************************
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// To read the license please visit http://www.gnu.org/copyleft/gpl.html
// *********************************************************************

#include <gsCore/log.h>
#include <gsServer/sessionevents.h>

#include <osSOEProtocol/encryption.h>
#include <osSOEProtocol/compression.h>
#include <osSOEProtocol/soesession.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soelayermessages.h>
using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

SOESession::SOESession(gsNetwork::NetworkAddressPtr address, gsNetwork::GameSocket *socket)
: Session(address, socket)
{
	setValid(false);
}

void SOESession::processIncomingQueue()
{
	if (! m_incomingQueue.size())
		return;

	std::list<BinaryPacketPtr>::iterator itor = 
		m_incomingQueue.begin();

	for (; itor != m_incomingQueue.end();)
	{
		(*itor)->setReadPosition(0);
		handleSOELayer(*itor);
		itor = m_incomingQueue.erase(itor);
	}
}

void SOESession::handleSOELayer(BinaryPacketPtr packet) {
	if ((packet->getLength() - (packet->getReadPosition())) < 2)
		return;

	uint16 opcode = packet->read<uint16>();

	switch(opcode)
	{
	case SOE_MULTI_PKT:
		{
			boost::shared_ptr<MultiMessage> message(GS_NEW MultiMessage(packet));
			message->unserialize();

			std::list<BinaryPacketPtr>::iterator i = message->segments.begin();

			while (i != message->segments.end())
			{
				handleSOELayer(*i);
				i = message->segments.erase(i);
			}
		}
		break;

	case SOE_DISCONNECT:
		{
			boost::shared_ptr<DisconnectMessage> message(GS_NEW DisconnectMessage(packet));
			message->unserialize();
			
			safeTriggerEvent(Event_DisconnectRequested(message, this));
		}
		break;

	case SOE_NET_STATUS_REQ:
		{
			boost::shared_ptr<NetStatusRequestMessage> message(GS_NEW NetStatusRequestMessage(packet));
			message->unserialize();

			boost::shared_ptr<NetStatusResponseMessage> response(GS_NEW NetStatusResponseMessage());
			response->tick = message->tick;
			sendToRemote(response);
		}
		break;

	case SOE_CHL_DATA_A:
		{
			boost::shared_ptr<DataChannelMessage> message(GS_NEW DataChannelMessage(packet));
			message->unserialize();

			setClientSequence(message->clientSequence);

			std::list<BinaryPacketPtr>::iterator i = message->segments.begin();
	
			while (i != message->segments.end())
			{
				processClientCommand(*i);
				i = message->segments.erase(i);			
			}
		}
		break;

	case SOE_ACK_A:
		{
			boost::shared_ptr<AcknowledgeMessage> message(GS_NEW AcknowledgeMessage(packet));
			message->unserialize();

			safeTriggerEvent(Event_Acknowledge(message, this));
		}
		break;

	default:
		{
			processClientCommand(packet);
		}
	}
}

void SOESession::processClientCommand(gsNetwork::BinaryPacketPtr packet)
{
	if (packet->getLength() < 4)
		return;

	uint32 opcode = packet->read<uint32>();

	boost::optional<OpcodeHandlerPtr> handler = m_opcodeFactory->findOpcodeHandler(opcode);

	if (! handler)
	{
		Log::getMainLog().error("Invalid opcode recieved: [0x%08x] %s", opcode, getRemoteAddress()->getAddressString().c_str());
		return;
	}

	(*handler)->handle(this, packet);
}

