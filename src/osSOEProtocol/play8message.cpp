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

#include <osSOEProtocol/play8message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Play8Message::Play8Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Play8Message::Play8Message(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Play8Message::~Play8Message()
{}

std::shared_ptr<BinaryPacket> Play8Message::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());

	*packet << (uint16_t)5;
	*packet << (uint32_t)SMSG_OBJ_UPDATE;
	*packet << (uint64_t)objectId+7;
    *packet << (uint32_t)0x504C4159;
    *packet << (uint8_t)8;

	*packet << (uint32_t)76; // Size without lists
	*packet << (uint16_t)7;

	*packet << (uint32_t)0; // XP list
	*packet << (uint32_t)0;

	*packet << (uint32_t)0; // Waypoint list
	*packet << (uint32_t)0;

	*packet << (uint32_t)0; // Current force
	*packet << (uint32_t)0; // Max force

	*packet << (uint32_t)5;	// unk					 
	*packet << (uint64_t)14;	// unk			// used to be 20
	*packet << (uint8_t)0;		// unk
	*packet << (uint32_t)5;	// unk
	*packet << (uint64_t)14;	// unk			// used to be 20

	*packet << (uint8_t)0;		// unk

	*packet << (uint32_t)0; // Quest list
	*packet << (uint32_t)0;

	*packet << (uint32_t)0;

	*packet << (uint8_t)1 << (uint32_t)0 << (uint8_t)0x64 << (uint8_t)0xEA << (uint16_t)0;

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Play8Message::unserialize()
{
}

