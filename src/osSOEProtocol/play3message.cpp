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

#include <osSOEProtocol/play3message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Play3Message::Play3Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Play3Message::Play3Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Play3Message::~Play3Message()
{}

BinaryPacketPtr Play3Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)SMSG_OBJ_UPDATE;
    *packet << (uint64)objectId+7; // id+offset

    // Object Packet Type (CREO3)
    *packet << (uint32)0x504C4159;
    *packet << (uint8)3;

    *packet << (uint32)127;

	//WTF
	*packet << (uint16)0x000B; // Maybe subop count?
	*packet << (uint32)0x3F800000; // (float)1.0
    
	*packet << (uint16)0x0F; //string size
    packet->append<std::string>(std::string("string_id_table"));    
	
	//Wierd Shit Here
	*packet << (uint64)0;
	*packet << (uint64)0;
	*packet << (uint16)0;
	*packet << (uint64)4;
	*packet << (uint64)0;
	*packet << (uint32)0;
	*packet << (uint64)4;
	*packet << (uint64)0;
	*packet << (uint32)0;

    *packet << (uint16)0; // Title (string)

    *packet << (uint32)0x0000059B; // Figure out what these do
    *packet << (uint32)0x001FEFD2;
    *packet << (uint32)0x0000001E;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Play3Message::unserialize()
{
}

