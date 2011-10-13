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

#include <osSOEProtocol/tano9message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Tano9Message::Tano9Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Tano9Message::Tano9Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Tano9Message::~Tano9Message()
{}

BinaryPacketPtr Tano9Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);
    // Send TANO 9
    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)SMSG_OBJ_UPDATE;
    *packet << (uint64_t)objectId;

    // Object Packet Type (CREO3)
    *packet << "ONAT" << (uint8_t)9;
    *packet << (uint32_t)2;                                     //Unknown
    *packet << (uint16_t)0;                                     //Object Operand

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Tano9Message::unserialize()
{
}

