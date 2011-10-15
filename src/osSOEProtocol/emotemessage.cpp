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

#include <osSOEProtocol/emotemessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

EmoteMessage::EmoteMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

EmoteMessage::EmoteMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

EmoteMessage::~EmoteMessage()
{}
		
std::shared_ptr<NetworkMessage> EmoteMessage::clone()
{
	std::shared_ptr<EmoteMessage> clone(GS_NEW EmoteMessage);
	clone->objectId = objectId; // Target (this is the character moving)
	clone->targetId = targetId;
	clone->emoteId = emoteId;

	return clone;
}

std::shared_ptr<BinaryPacket> EmoteMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());

    *packet << (uint16_t)5;
    *packet << (uint32_t)AMSG_INT_PACKET;
    *packet << (uint32_t)0xB;
    *packet << (uint32_t)0x012E;
    *packet << (uint64_t)recipientId; //recipient
    *packet << (uint32_t)0; //unkown
    *packet << (uint64_t)objectId; //source
    *packet << (uint64_t)targetId; //This is normally the target...
    *packet << (uint16_t)emoteId; //ID
    *packet << (uint8_t)0;
    *packet << (uint16_t)0x0300;

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void EmoteMessage::unserialize()
{
}

