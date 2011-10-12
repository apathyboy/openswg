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

#include <osSOEProtocol/selfpostureupdatemessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

SelfPostureUpdateMessage::SelfPostureUpdateMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

SelfPostureUpdateMessage::SelfPostureUpdateMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

SelfPostureUpdateMessage::~SelfPostureUpdateMessage()
{}

		
boost::shared_ptr<NetworkMessage> SelfPostureUpdateMessage::clone()
{
	boost::shared_ptr<SelfPostureUpdateMessage> clone(GS_NEW SelfPostureUpdateMessage);
	clone->objectId = objectId; // Target (this is the character moving)
	clone->posture = posture;

	return clone;
}


BinaryPacketPtr SelfPostureUpdateMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
	
    *packet << (uint16_t)5;
    *packet << (uint32_t)AMSG_INT_PACKET;
    *packet << (uint32_t)27;
    *packet << (uint32_t)305;
    *packet << (uint64_t)objectId;
    *packet << (uint32_t)0;
    *packet << (uint8_t)posture;
    *packet << (uint8_t)1;

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void SelfPostureUpdateMessage::unserialize()
{
}

