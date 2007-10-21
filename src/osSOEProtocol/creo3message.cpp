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

Creo3Message::Creo3Message(BinaryPacketPtr packet)
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

BinaryPacketPtr Creo3Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)SMSG_OBJ_UPDATE;
    *packet << (uint64)objectId;

    // Object Packet Type (CREO3)
    *packet << (uint32)0x4352454F;
    *packet << (uint8)3;
    
    *packet << (uint32)(149 + category.length() + appearance.length() + type.length() + (fullname.length() * 2));
    *packet << (uint16)12;

    *packet << (uint32)16256;

    *packet << (uint16)category.length();
    packet->append<std::string>(category);

    *packet << (uint32)0;

    *packet << (uint16)type.length();
    packet->append<std::string>(type);

    *packet << (uint32)fullname.length();
    for (uint i = 0; i < fullname.length(); ++i)
        *packet << (unicode)fullname.c_str()[i];

    *packet << (uint32)1000000;

    *packet << (uint16)appearance.length();
	if (appearance.length()>0)
		packet->append<std::string>(appearance);

    // 7 unk uint32's default
    //FIX ME - XENO
    *packet << (uint32)1; 
    *packet << (uint32)0; 
    *packet << (uint32)0; 
    *packet << (uint32)128; 
    *packet << (uint32)0; 
    *packet << (uint32)0; 
    *packet << (uint32)3000; 

    *packet << (uint8)1;

    *packet << (uint8)posture << (uint8)0; // Posture id    
    *packet << (uint64)targetId; // Target
    *packet << (float)scale; // Height
    *packet << (uint32)battleFatigue; // Battle Fatigue
    *packet << (uint64)0; // State

    *packet << (uint32)9;
    *packet << (uint32)9;

	*packet << (uint32)healthWounds;
	*packet << (uint32)strengthWounds;
	*packet << (uint32)constitutionWounds;
	*packet << (uint32)actionWounds;
	*packet << (uint32)quicknessWounds;
	*packet << (uint32)staminaWounds;
	*packet << (uint32)mindWounds;
	*packet << (uint32)focusWounds;
	*packet << (uint32)willpowerWounds;

    for (int i = 0; i < 9; ++i)
        *packet << (uint32)0;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Creo3Message::unserialize()
{
}

