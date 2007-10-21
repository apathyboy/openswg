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

EmoteMessage::EmoteMessage(BinaryPacketPtr packet)
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
		
boost::shared_ptr<NetworkMessage> EmoteMessage::clone()
{
	boost::shared_ptr<EmoteMessage> clone(GS_NEW EmoteMessage);
	clone->objectId = objectId; // Target (this is the character moving)
	clone->targetId = targetId;
	clone->emoteId = emoteId;

	return clone;
}

BinaryPacketPtr EmoteMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());

    *packet << (uint16)5;
    *packet << (uint32)AMSG_INT_PACKET;
    *packet << (uint32)0xB;
    *packet << (uint32)0x012E;
    *packet << (uint64)recipientId; //recipient
    *packet << (uint32)0; //unkown
    *packet << (uint64)objectId; //source
    *packet << (uint64)targetId; //This is normally the target...
    *packet << (uint16)emoteId; //ID
    *packet << (uint8)0;
    *packet << (uint16)0x0300;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void EmoteMessage::unserialize()
{
}

