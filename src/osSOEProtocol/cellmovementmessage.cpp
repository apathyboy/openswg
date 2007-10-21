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

#include <osSOEProtocol/cellmovementmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soepackettools.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

CellMovementMessage::CellMovementMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

CellMovementMessage::CellMovementMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

CellMovementMessage::~CellMovementMessage()
{}
		
boost::shared_ptr<NetworkMessage> CellMovementMessage::clone()
{
	boost::shared_ptr<CellMovementMessage> clone(GS_NEW CellMovementMessage);
	clone->objectId = objectId; // Target (this is the character moving)
    clone->ticks = ticks; // Ticks?
    clone->timer = timer; // Times?
    clone->direction = direction;
	clone->cellId = cellId;
    clone->quaternionX = quaternionX; // Orientation x
    clone->quaternionY = quaternionY; // Orientation y
    clone->quaternionZ = quaternionZ; // Orientation z
    clone->quaternionW = quaternionW; // Orientation w
    clone->positionX = positionX; // position x
    clone->positionY = positionY; // position y
    clone->positionZ = positionZ; // position z
    clone->speed = speed; // speed
	clone->orientation = orientation;

	return clone;
}

BinaryPacketPtr CellMovementMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);
    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)8;

	*packet << (uint32)SMSG_CELL_POS_UPDATE;
	*packet << cellId;
	*packet << objectId;

    *packet << (uint16)((positionX * 8.f));
	*packet << (uint16)((positionY * 8.f));
	*packet << (uint16)((positionZ * 8.f));

	*packet << (uint32)(timer+1);

	*packet << (uint8)0; 
    *packet << (uint8)direction;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void CellMovementMessage::unserialize()
{
	objectId = m_serializedData->read<uint64>(); // Target (this is the character moving)
    ticks = m_serializedData->read<uint32>(); // Ticks?
    timer = m_serializedData->read<uint32>(); // Times?
	cellId = m_serializedData->read<uint64>(); // Cell id
    quaternionX = m_serializedData->read<float>(); // Quaternion x
    quaternionY = m_serializedData->read<float>(); // Quaternion y
    quaternionZ = m_serializedData->read<float>(); // Quaternion z
    quaternionW = m_serializedData->read<float>(); // Quaternion w
    positionX = m_serializedData->read<float>(); // position x
    positionY = m_serializedData->read<float>(); // position y
    positionZ = m_serializedData->read<float>(); // position z
    speed = m_serializedData->read<float>(); // speed
}
