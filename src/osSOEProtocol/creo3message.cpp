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

#include <osSOEProtocol/creo3message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Creo3Message::Creo3Message()
: NetworkMessage()
{
	setPriority(0);
	posture = 0;
	setResend(true);
	setEncrypt(true);
	targetId = 0;
	setCrc(true);
}

Creo3Message::Creo3Message(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	posture = 0;
	setEncrypt(true);
	targetId = 0;
	setCrc(true);
	m_serializedData = packet;
}

Creo3Message::~Creo3Message()
{}

std::shared_ptr<BinaryPacket> Creo3Message::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)SMSG_OBJ_UPDATE;
    *packet << (uint64_t)objectId;

    // Object Packet Type (CREO3)
    *packet << (uint32_t)0x4352454F;
    *packet << (uint8_t)3;
    
    *packet << (uint32_t)(149 + category.length() + appearance.length() + type.length() + (fullname.length() * 2));
    *packet << (uint16_t)12;

    *packet << (uint32_t)16256;

    *packet << (uint16_t)category.length();
    packet->append<std::string>(category);

    *packet << (uint32_t)0;

    *packet << (uint16_t)type.length();
    packet->append<std::string>(type);

    *packet << (uint32_t)fullname.length();
    for (uint32_t i = 0; i < fullname.length(); ++i)
        *packet << (uint16_t)fullname.c_str()[i];

    *packet << (uint32_t)1000000;

    *packet << (uint16_t)appearance.length();
	if (appearance.length()>0)
		packet->append<std::string>(appearance);

    // 7 unk uint32's default
    //FIX ME - XENO
    *packet << (uint32_t)1; 
    *packet << (uint32_t)0; 
    *packet << (uint32_t)0; 
    *packet << (uint32_t)128; 
    *packet << (uint32_t)0; 
    *packet << (uint32_t)0; 
    *packet << (uint32_t)3000; 

    *packet << (uint8_t)1;

    *packet << (uint8_t)posture << (uint8_t)0; // Posture id    
    *packet << (uint64_t)targetId; // Target
    *packet << (float)scale; // Height
    *packet << (uint32_t)battleFatigue; // Battle Fatigue
    *packet << (uint64_t)0; // State

    *packet << (uint32_t)9;
    *packet << (uint32_t)9;

	*packet << (uint32_t)healthWounds;
	*packet << (uint32_t)strengthWounds;
	*packet << (uint32_t)constitutionWounds;
	*packet << (uint32_t)actionWounds;
	*packet << (uint32_t)quicknessWounds;
	*packet << (uint32_t)staminaWounds;
	*packet << (uint32_t)mindWounds;
	*packet << (uint32_t)focusWounds;
	*packet << (uint32_t)willpowerWounds;

    for (int i = 0; i < 9; ++i)
        *packet << (uint32_t)0;

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Creo3Message::unserialize()
{
}

