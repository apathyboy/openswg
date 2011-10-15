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

#include <osSOEProtocol/pingmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

PingMessage::PingMessage()
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setCrc(false);
}

PingMessage::PingMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setCrc(false);
	m_serializedData = packet;
}

PingMessage::~PingMessage()
{}

BinaryPacketPtr PingMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);
    *packet << (uint16_t)SOE_SESSION_RESPONSE;
    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void PingMessage::unserialize()
{
}

