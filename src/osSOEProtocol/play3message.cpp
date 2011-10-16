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

#include <boost/asio.hpp>

#include <osSOEProtocol/opcodes.h>

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

Play3Message::Play3Message(std::shared_ptr<BinaryPacket> packet)
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

std::shared_ptr<BinaryPacket> Play3Message::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)SMSG_OBJ_UPDATE;
    *packet << (uint64_t)objectId+7; // id+offset

    // Object Packet Type (CREO3)
    *packet << (uint32_t)0x504C4159;
    *packet << (uint8_t)3;

    *packet << (uint32_t)127;

	//WTF
	*packet << (uint16_t)0x000B; // Maybe subop count?
	*packet << (uint32_t)0x3F800000; // (float)1.0
    
	*packet << (uint16_t)0x0F; //string size
    packet->append<std::string>(std::string("string_id_table"));    
	
	//Wierd Shit Here
	*packet << (uint64_t)0;
	*packet << (uint64_t)0;
	*packet << (uint16_t)0;
	*packet << (uint64_t)4;
	*packet << (uint64_t)0;
	*packet << (uint32_t)0;
	*packet << (uint64_t)4;
	*packet << (uint64_t)0;
	*packet << (uint32_t)0;

    *packet << (uint16_t)0; // Title (string)

    *packet << (uint32_t)0x0000059B; // Figure out what these do
    *packet << (uint32_t)0x001FEFD2;
    *packet << (uint32_t)0x0000001E;

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Play3Message::unserialize()
{
}

