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

#include "osSOEProtocol/soesession.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsServer/sessionevents.h>

#include <osSOEProtocol/encryption.h>
#include <osSOEProtocol/compression.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soelayermessages.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

SOESession::SOESession(std::shared_ptr<gsNetwork::NetworkAddress> address, std::shared_ptr<gsNetwork::UdpEventSocket> socket)
: Session(address, socket)
{
	setValid(false);
}

void SOESession::processIncomingQueue()
{
	if (! m_incomingQueue.size())
		return;

	std::list<std::shared_ptr<BinaryPacket>>::iterator itor = 
		m_incomingQueue.begin();

	for (; itor != m_incomingQueue.end();)
	{
		(*itor)->setReadPosition(0);
		handleSOELayer(*itor);
		itor = m_incomingQueue.erase(itor);
	}
}

void SOESession::handleSOELayer(std::shared_ptr<BinaryPacket> packet) {
	if ((packet->getLength() - (packet->getReadPosition())) < 2)
		return;

	uint16_t opcode = packet->read<uint16_t>();

	switch(opcode)
	{
	case SOE_MULTI_PKT:
		{
			std::shared_ptr<MultiMessage> message(GS_NEW MultiMessage(packet));
			message->unserialize();

			std::list<std::shared_ptr<BinaryPacket>>::iterator i = message->segments.begin();

			while (i != message->segments.end())
			{
				handleSOELayer(*i);
				i = message->segments.erase(i);
			}
		}
		break;

	case SOE_DISCONNECT:
		{
			std::shared_ptr<DisconnectMessage> message(GS_NEW DisconnectMessage(packet));
			message->unserialize();
			
			safeTriggerEvent(Event_DisconnectRequested(message, this));
		}
		break;

	case SOE_NET_STATUS_REQ:
		{
			std::shared_ptr<NetStatusRequestMessage> message(GS_NEW NetStatusRequestMessage(packet));
			message->unserialize();

			std::shared_ptr<NetStatusResponseMessage> response(GS_NEW NetStatusResponseMessage());
			response->tick = message->tick;
			sendToRemote(response);
		}
		break;

	case SOE_CHL_DATA_A:
		{
			std::shared_ptr<DataChannelMessage> message(GS_NEW DataChannelMessage(packet));
			message->unserialize();

			setClientSequence(message->clientSequence);

			std::list<std::shared_ptr<BinaryPacket>>::iterator i = message->segments.begin();
	
			while (i != message->segments.end())
			{
				processClientCommand(*i);
				i = message->segments.erase(i);			
			}
		}
		break;

	case SOE_ACK_A:
		{
			std::shared_ptr<AcknowledgeMessage> message(GS_NEW AcknowledgeMessage(packet));
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

void SOESession::processClientCommand(std::shared_ptr<gsNetwork::BinaryPacket> packet)
{
	if (packet->getLength() < 4)
		return;

	uint32_t opcode = packet->read<uint32_t>();

	boost::optional<OpcodeHandlerPtr> handler = m_opcodeFactory->findOpcodeHandler(opcode);

	if (! handler)
	{
        LOG(ERROR) << "Invalid opcode received: " << std::hex << opcode ;
		return;
	}

	(*handler)->handle(this, packet);
}

