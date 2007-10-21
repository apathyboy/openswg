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

#include <osSOEProtocol/play9updatemessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Play9UpdateMessage::Play9UpdateMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Play9UpdateMessage::Play9UpdateMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Play9UpdateMessage::~Play9UpdateMessage()
{}

BinaryPacketPtr Play9UpdateMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)2;
    *packet << (uint32)SMSG_DELTA_UPDATE;
    *packet << (uint64)objectId+12; // id+offset
	*packet << (uint8)0x59 << (uint8)0x41 << (uint8)0x4C << (uint8)0x50; // PLAY (YALP)
    *packet << (uint8)9;

	// Size
	*packet << (uint8)0x1C << (uint8)0x00 << (uint8)0x00 << (uint8)0x00, 
	*packet << (uint16)2; // ??
	*packet << (uint16)7; // ??

	*packet << (uint32)1; // List size
	*packet << (uint32)2; // This is double the first, maybe its used for measuring the beginning and end?

	*packet << (uint16)3; // // Size 
	*packet << (uint8)0; // byte buffer

	*packet << (uint16)8; // ??
	*packet << (uint32)1; // list size
	*packet << (uint32)2; // list size double
	*packet << (uint16)3; // Size
	*packet << (uint8)0; // Byte buffer

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Play9UpdateMessage::unserialize()
{
}

