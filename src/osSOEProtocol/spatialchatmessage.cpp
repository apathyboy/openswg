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
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

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

SpatialChatMessage::SpatialChatMessage(BinaryPacketPtr packet)
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
		
boost::shared_ptr<NetworkMessage> SpatialChatMessage::clone()
{
	boost::shared_ptr<SpatialChatMessage> clone(GS_NEW SpatialChatMessage);
	clone->message = this->message;
	clone->targetId = this->targetId;
	clone->moods = this->moods;	

	return clone;
}


BinaryPacketPtr SpatialChatMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);
    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)AMSG_INT_PACKET;
    *packet << (uint32)0x0000000B;
    *packet << (uint32)0x000000F4;
    *packet << (uint64)recipientId; // recipient
    *packet << (uint32)0x00000000; // unknown
    *packet << (uint64)targetId; //source

    *packet << (uint64)moods[0]; // No mood or target mood for now.

    *packet << (uint32)message.length();

    for (uint j = 0; j < message.length(); ++j)
        *packet << (unicode)message.c_str()[j];

    *packet << (uint16)0x0032; 
    *packet << (uint16)moods[1];
    *packet << (uint16)moods[2];
    *packet << (uint16)0x0100;
    *packet << (uint64)0;

    *packet << (uint8)0 << (uint16)0;
	return packet;
}

void SpatialChatMessage::unserialize()
{
}

