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

#include <osSOEProtocol/spatialchatmessage.h>

#include <boost/asio.hpp>

#include <osSOEProtocol/opcodes.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

SpatialChatMessage::SpatialChatMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

SpatialChatMessage::SpatialChatMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setEncrypt(true);
	setResend(true);
	setCrc(true);
	m_serializedData = packet;
}

SpatialChatMessage::~SpatialChatMessage()
{}
		
std::shared_ptr<NetworkMessage> SpatialChatMessage::clone()
{
	std::shared_ptr<SpatialChatMessage> clone(new SpatialChatMessage);
	clone->message = this->message;
	clone->targetId = this->targetId;
	clone->moods = this->moods;	

	return clone;
}


std::shared_ptr<BinaryPacket> SpatialChatMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);
    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)AMSG_INT_PACKET;
    *packet << (uint32_t)0x0000000B;
    *packet << (uint32_t)0x000000F4;
    *packet << (uint64_t)recipientId; // recipient
    *packet << (uint32_t)0x00000000; // unknown
    *packet << (uint64_t)targetId; //source

    *packet << (uint64_t)moods[0]; // No mood or target mood for now.

    *packet << (uint32_t)message.length();

    for (uint32_t j = 0; j < message.length(); ++j)
        *packet << (uint16_t)message.c_str()[j];

    *packet << (uint16_t)0x0032; 
    *packet << (uint16_t)moods[1];
    *packet << (uint16_t)moods[2];
    *packet << (uint16_t)0x0100;
    *packet << (uint64_t)0;

    *packet << (uint8_t)0 << (uint16_t)0;
	return packet;
}

void SpatialChatMessage::unserialize()
{
}

