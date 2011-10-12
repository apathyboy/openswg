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

#include <osSOEProtocol/play9message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Play9Message::Play9Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Play9Message::Play9Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Play9Message::~Play9Message()
{}

BinaryPacketPtr Play9Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());

	*packet << (uint16_t)5;
	*packet << (uint32_t)SMSG_OBJ_UPDATE;
	*packet << (uint64_t)objectId+7;
    *packet << (uint32_t)0x504C4159;
    *packet << (uint8_t)9;

	*packet << (uint32_t)98; // Size without lists.
	*packet << (uint32_t)11;
	
	*packet << (uint32_t)0;
	*packet << (uint32_t)0;
	

	*packet << (uint32_t)0; // unk
	*packet << (uint32_t)0; // unk

	/* Schematic list (The following puts a saber in the datapad's Draft Schematics)
	packet << (uint32)1; // unk
	packet << (uint32)1; // unk

	packet << (uint8)0;
	packet << (uint64)0x94BB8DC513020F2B;
	packet << (uint32)1;
	*/
	*packet << (uint32_t)0; // unk
	*packet << (uint32_t)0; // unk

	*packet << (uint32_t)0; // schematic list?
	*packet << (uint32_t)0; // schematic list?
	// this gave me an unknown schematic
	//packet << (uint8)0x03 << (uint8)0 << "F" << "U"; // unk list item?
	//packet << (uint8)0x03 << (uint8)0 << "F" << "U"; // unk list item?

	*packet << (uint32_t)8; // unk
	*packet << (uint32_t)0; // unk

	// Friend List
	*packet << (uint32_t)0; // unk list
	*packet << (uint32_t)0; // unk list

	// Ignore List
	*packet << (uint32_t)0; // unk list
	*packet << (uint32_t)0; // unk list

	*packet << (uint32_t)1; 

	*packet << (uint32_t)0; // Food fullness
	*packet << (uint32_t)100; // max food

	*packet << (uint32_t)0; // Drink fullness
	*packet << (uint32_t)100; // max drink

	*packet << (uint32_t)0; // unk
	*packet << (uint32_t)100; // unk


	*packet << (uint32_t)0; // unk
	*packet << (uint32_t)0; // unk list

	*packet << (uint32_t)1; // jedi flag 0=normal 1=force sensative 4=light rank 8=jedi force rank dark
/*
	*packet << (uint32)0; // Skill Abilities and Cert list
	*packet << (uint32)0;

	*packet << (uint32)0; // unk
	*packet << (uint32)0; // unk
	*packet << (uint64)0; // unk

	*packet << (uint32)0; // Schematic list
	*packet << (uint32)0; 

	*packet << (uint32)0; // unk
	*packet << (uint32)0; // unk
	*packet << (uint64)0; // unk list
	*packet << (uint64)0; // unk list
	*packet << (uint32)0; // unk
	
	*packet << (uint32)0; // Food fullness
	*packet << (uint32)100; // max food
	*packet << (uint32)0; // drink fullness
	*packet << (uint32)100; // max drink

	*packet << (uint32)0; // unk
	*packet << (uint32)64; // unk			// This was 0
	*packet << (uint64)0; // unk list
	*packet << (uint32)64; // unk			// This was 0

	*packet << (uint32)1;					// this wasnt here
*/
    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Play9Message::unserialize()
{
}

