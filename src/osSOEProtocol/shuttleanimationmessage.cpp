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

#include <osSOEProtocol/shuttleanimationmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

ShuttleAnimationMessage::ShuttleAnimationMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

ShuttleAnimationMessage::ShuttleAnimationMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

ShuttleAnimationMessage::~ShuttleAnimationMessage()
{}

BinaryPacketPtr ShuttleAnimationMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);
    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());

    *packet << (uint16)htonl(25);

    *packet << (uint8)28;
    *packet << (uint32)SMSG_DELTA_UPDATE;
    *packet << (uint64)objectId;
    *packet << (uint32)0x4352454F;
    *packet << (uint8)3;
    *packet << (uint32)5;
    *packet << (uint16)1;
    *packet << (uint16)11;
    *packet << (uint8)posture;
    
    *packet << (uint8)56;
    *packet << (uint16)5;
    *packet << (uint32)AMSG_INT_PACKET;
    *packet << (uint32)27;
    *packet << (uint32)204;
    *packet << (uint64)objectId;
    *packet << (uint32)0;
    *packet << (uint32)0xab290245; // Animation crc?
    *packet << (uint64)objectId;
    *packet << (uint64)0;
    *packet << (uint64)posture;
    *packet << (uint16)0;

    *packet << (uint8)28;
    *packet << (uint16)5;
    *packet << (uint32)AMSG_INT_PACKET;
    *packet << (uint32)27;
    *packet << (uint32)305;
    *packet << (uint64)objectId;
    *packet << (uint32)0;
    *packet << (uint8)posture;
    *packet << (uint8)1;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void ShuttleAnimationMessage::unserialize()
{
}

