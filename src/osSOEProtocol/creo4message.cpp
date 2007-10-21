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

#include <osSOEProtocol/creo4message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Creo4Message::Creo4Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Creo4Message::Creo4Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Creo4Message::~Creo4Message()
{}

BinaryPacketPtr Creo4Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());

	*packet << (uint16)5;

	*packet << (uint32)SMSG_OBJ_UPDATE;
	*packet << (uint64)objectId;
	*packet << (uint32)0x4352454F << (uint8)4;
	*packet << (uint32)86; // Size without skills

	*packet << (uint16)14; // Object count
	*packet << (float)1.0;
	*packet << (float)1.0; 
	
    *packet << (uint32)3;  // Ham encumbrence
    *packet << (uint32)3;

    for (int i = 0; i < 3; ++i)
        *packet << (uint32)0;

	*packet << (uint32)0; // Skill list size
	*packet << (uint32)0;
	
    *packet << (float)1.0; //unknown
    *packet << (float)1.f; // Acceleration?
    *packet << (uint64)0; // unknown
    *packet << (float)5.376f; // Players Running Speed.
    *packet << (float)0.453786; // unknown
    *packet << (float)0.0125; // unknown
    *packet << (float)1.0; // unknown
    *packet << (float)1.549; // unknown
    *packet << (float)0.75; // unknown
    *packet << (uint64)0; // unknown

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Creo4Message::unserialize()
{
}

