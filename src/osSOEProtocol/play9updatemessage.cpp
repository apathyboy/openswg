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

#include <boost/asio.hpp>

#include <osSOEProtocol/opcodes.h>

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

Play9UpdateMessage::Play9UpdateMessage(std::shared_ptr<BinaryPacket> packet)
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

std::shared_ptr<BinaryPacket> Play9UpdateMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)2;
    *packet << (uint32_t)SMSG_DELTA_UPDATE;
    *packet << (uint64_t)objectId+12; // id+offset
	*packet << (uint8_t)0x59 << (uint8_t)0x41 << (uint8_t)0x4C << (uint8_t)0x50; // PLAY (YALP)
    *packet << (uint8_t)9;

	// Size
	*packet << (uint8_t)0x1C << (uint8_t)0x00 << (uint8_t)0x00 << (uint8_t)0x00, 
	*packet << (uint16_t)2; // ??
	*packet << (uint16_t)7; // ??

	*packet << (uint32_t)1; // List size
	*packet << (uint32_t)2; // This is double the first, maybe its used for measuring the beginning and end?

	*packet << (uint16_t)3; // // Size 
	*packet << (uint8_t)0; // byte buffer

	*packet << (uint16_t)8; // ??
	*packet << (uint32_t)1; // list size
	*packet << (uint32_t)2; // list size double
	*packet << (uint16_t)3; // Size
	*packet << (uint8_t)0; // Byte buffer

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Play9UpdateMessage::unserialize()
{
}

