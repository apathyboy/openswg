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

Creo1Message::Creo1Message(std::shared_ptr<BinaryPacket> packet)
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

std::shared_ptr<BinaryPacket> Creo1Message::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());

	*packet << (uint16_t)5;
	*packet << (uint32_t)SMSG_OBJ_UPDATE;
	*packet << (uint64_t)objectId;

	*packet << (uint32_t)0x4352454F << (uint8_t)1;

	*packet << (uint32_t)62; // Packet size (without skills)
	*packet << (uint16_t)4;
	*packet << (uint32_t)bankCredits; // Bank credits
	*packet << (uint32_t)inventoryCredits; // Inventory credits

    *packet << (uint32_t)9;  // Ham modifiers
    *packet << (uint32_t)9;

	*packet << (uint32_t)healthModifiers;
	*packet << (uint32_t)strengthModifiers;
	*packet << (uint32_t)constitutionModifiers;
	*packet << (uint32_t)actionModifiers;
	*packet << (uint32_t)quicknessModifiers;
	*packet << (uint32_t)staminaModifiers;
	*packet << (uint32_t)mindModifiers;
	*packet << (uint32_t)focusModifiers;
	*packet << (uint32_t)willpowerModifiers;

	*packet << (uint64_t)0; // Skill list

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Creo1Message::unserialize()
{
}

