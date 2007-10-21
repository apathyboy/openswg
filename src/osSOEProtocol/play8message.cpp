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

Play8Message::Play8Message(BinaryPacketPtr packet)
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

BinaryPacketPtr Play8Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());

	*packet << (uint16)5;
	*packet << (uint32)SMSG_OBJ_UPDATE;
	*packet << (uint64)objectId+7;
    *packet << (uint32)0x504C4159;
    *packet << (uint8)8;

	*packet << (uint32)76; // Size without lists
	*packet << (uint16)7;

	*packet << (uint32)0; // XP list
	*packet << (uint32)0;

	*packet << (uint32)0; // Waypoint list
	*packet << (uint32)0;

	*packet << (uint32)0; // Current force
	*packet << (uint32)0; // Max force

	*packet << (uint32)5;	// unk					 
	*packet << (uint64)14;	// unk			// used to be 20
	*packet << (uint8)0;		// unk
	*packet << (uint32)5;	// unk
	*packet << (uint64)14;	// unk			// used to be 20

	*packet << (uint8)0;		// unk

	*packet << (uint32)0; // Quest list
	*packet << (uint32)0;

	*packet << (uint32)0;

	*packet << (uint8)1 << (uint32)0 << (uint8)0x64 << (uint8)0xEA << (uint16)0;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Play8Message::unserialize()
{
}

