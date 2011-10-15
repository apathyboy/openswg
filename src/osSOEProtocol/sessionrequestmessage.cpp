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

#include <osSOEProtocol/sessionrequestmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

SessionRequestMessage::SessionRequestMessage()
: NetworkMessage()
{
	setPriority(0);
}

SessionRequestMessage::SessionRequestMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	m_serializedData = packet;
}

SessionRequestMessage::~SessionRequestMessage()
{}

std::shared_ptr<BinaryPacket> SessionRequestMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

	return packet;
}

void SessionRequestMessage::unserialize()
{
	m_serializedData->read<uint32_t>(); // Skip ahead to the data we want.

	connectionId  = m_serializedData->read<uint32_t>();
    maxPacketSize = (uint32_t)ntohl(m_serializedData->read<uint32_t>());
}

