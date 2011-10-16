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

#include <osSOEProtocol/sessionresponsemessage.h>

#include <boost/asio.hpp>

#include <osSOEProtocol/opcodes.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

SessionResponseMessage::SessionResponseMessage()
{
	setPriority(0);
}

SessionResponseMessage::SessionResponseMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	m_serializedData = packet;
}

SessionResponseMessage::~SessionResponseMessage()
{}

std::shared_ptr<BinaryPacket> SessionResponseMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);
    *packet << (uint16_t)SOE_SESSION_RESPONSE;
    *packet << (uint32_t)this->connectionId;
    *packet << (uint32_t)htonl(this->crcSeed);
    *packet << (uint8_t)2;
    *packet << (uint8_t)1;
    *packet << (uint8_t)4;
    *packet << (uint32_t)htonl(this->maxPacketSize);

	return packet;
}

void SessionResponseMessage::unserialize()
{
}

