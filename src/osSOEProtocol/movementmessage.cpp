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

#include <gsCore/timing.h>
#include <osSOEProtocol/movementmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soepackettools.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

MovementMessage::MovementMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_lastUpdateTime = 0;
	movedX = false;
	movedY = false;
	movedZ = false;
}

MovementMessage::MovementMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
	m_lastUpdateTime = 0;
	movedX = false;
	movedY = false;
	movedZ = false;
}

MovementMessage::~MovementMessage()
{}

bool MovementMessage::canSendScheduled()
{
	uint64 m_currentTime = gsCore::getTimeInMs();

	if (m_currentTime - m_lastUpdateTime > 300)
	{
		m_lastUpdateTime = m_currentTime;
		return true;
	}
	else
		return false;
}
		
boost::shared_ptr<NetworkMessage> MovementMessage::clone()
{
	boost::shared_ptr<MovementMessage> clone(GS_NEW MovementMessage);
	clone->objectId = this->objectId; // Target (this is the character moving)
    clone->ticks = this->ticks; // Ticks?
    clone->timer = this->timer; // Times?
    clone->direction = this->direction;
    clone->quaternionX = this->quaternionX; // Orientation x
    clone->quaternionY = this->quaternionY; // Orientation y
    clone->quaternionZ = this->quaternionZ; // Orientation z
    clone->quaternionW = this->quaternionW; // Orientation w
    clone->positionX = this->positionX; // position x
    clone->positionY = this->positionY; // position y
    clone->positionZ = this->positionZ; // position z
    clone->speed = this->speed; // speed
	clone->orientation = this->orientation;

	return clone;
}

BinaryPacketPtr MovementMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);
    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)8;

	*packet << (uint32)SMSG_POS_UPDATE;
    *packet << objectId;

	*packet << (uint16)((positionX * 4.f)+0.5f);
	*packet << (uint16)((positionY * 4.f)+0.5f);
	*packet << (uint16)((positionZ * 4.f)+0.5f);

	*packet << (uint32)(timer+1);

	*packet << (uint8)1; 
    *packet << (uint8)direction;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void MovementMessage::unserialize()
{
	objectId = m_serializedData->read<uint64>(); // Target (this is the character moving)
    ticks = m_serializedData->read<uint32>(); // Ticks?
    timer = m_serializedData->read<uint32>(); // Times?
    quaternionX = m_serializedData->read<float>(); // Quaternion x
    quaternionY = m_serializedData->read<float>(); // Quaternion y
    quaternionZ = m_serializedData->read<float>(); // Quaternion z
    quaternionW = m_serializedData->read<float>(); // Quaternion w
    positionX = m_serializedData->read<float>(); // position x
    positionY = m_serializedData->read<float>(); // position y
    positionZ = m_serializedData->read<float>(); // position z
    speed = m_serializedData->read<float>(); // speed
}

