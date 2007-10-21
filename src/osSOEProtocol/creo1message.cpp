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

#include <osSOEProtocol/creo1message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Creo1Message::Creo1Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Creo1Message::Creo1Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Creo1Message::~Creo1Message()
{}

BinaryPacketPtr Creo1Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());

	*packet << (uint16)5;
	*packet << (uint32)SMSG_OBJ_UPDATE;
	*packet << (uint64)objectId;

	*packet << (uint32)0x4352454F << (uint8)1;

	*packet << (uint32)62; // Packet size (without skills)
	*packet << (uint16)4;
	*packet << (uint32)bankCredits; // Bank credits
	*packet << (uint32)inventoryCredits; // Inventory credits

    *packet << (uint32)9;  // Ham modifiers
    *packet << (uint32)9;

	*packet << (uint32)healthModifiers;
	*packet << (uint32)strengthModifiers;
	*packet << (uint32)constitutionModifiers;
	*packet << (uint32)actionModifiers;
	*packet << (uint32)quicknessModifiers;
	*packet << (uint32)staminaModifiers;
	*packet << (uint32)mindModifiers;
	*packet << (uint32)focusModifiers;
	*packet << (uint32)willpowerModifiers;

	*packet << (uint64)0; // Skill list

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Creo1Message::unserialize()
{
}

