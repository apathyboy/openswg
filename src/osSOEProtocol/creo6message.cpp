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

#include <osSOEProtocol/creo6message.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soepackettools.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Creo6Message::Creo6Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	isPlayer=true;
}

Creo6Message::Creo6Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	isPlayer=true;
	m_serializedData = packet;
}

Creo6Message::~Creo6Message()
{}

BinaryPacketPtr Creo6Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)SMSG_OBJ_UPDATE;
    *packet << (uint64_t)objectId;

    // Object Packet Type (CREO3)
    *packet << (uint32_t)0x4352454F;
    *packet << (uint8_t)6;

    *packet << (uint32_t)437+mood.length();
    *packet << (uint16_t)22;
    *packet << (uint32_t)0; // Defender update counter
    *packet << (uint64_t)0; // Current defender

    *packet << (uint16_t)0; // Con level

    *packet << (uint16_t)0; // Music/Dance type

    //Mood String
    *packet << (uint16_t)mood.length();
	packet->append<std::string>(mood);

    *packet << (uint64_t)objectId + 5; // weao id

    *packet << (uint64_t)0; // Group id

    //unknowns FIX ME s
    *packet << (uint64_t)0;
    *packet << (uint64_t)0;
    *packet << (uint32_t)0; //
    *packet << (uint64_t)0;
    *packet << (uint8_t)0; //I was told that this wasmood.
    *packet << (uint32_t)0; //one of these might be GILD ID.
    *packet << (uint32_t)0; //

    *packet << (uint32_t)9; // list size for each HAM section
    *packet << (uint32_t)9; // 

	*packet << (uint32_t)currentHealth;
	*packet << (uint32_t)currentStrength;
	*packet << (uint32_t)currentConstitution;
	*packet << (uint32_t)currentAction;
	*packet << (uint32_t)currentQuickness;
	*packet << (uint32_t)currentStamina;
	*packet << (uint32_t)currentMind;
	*packet << (uint32_t)currentFocus;
	*packet << (uint32_t)currentWillpower;

    *packet << (uint32_t)9; // list size for each HAM section
    *packet << (uint32_t)9; // 

	*packet << (uint32_t)maxHealth;
	*packet << (uint32_t)maxStrength;
	*packet << (uint32_t)maxConstitution;
	*packet << (uint32_t)maxAction;
	*packet << (uint32_t)maxQuickness;
	*packet << (uint32_t)maxStamina;
	*packet << (uint32_t)maxMind;
	*packet << (uint32_t)maxFocus;
	*packet << (uint32_t)maxWillpower;

	if (isPlayer)
	{
    //EQUIPTMENT LIST FIX ME LATER
    *packet << (uint32_t)6; //List size for # of objects equipted
    *packet << (uint32_t)6; //176

    //weapon
    *packet << (uint16_t)0;
    *packet << (uint32_t)4;
    *packet << (uint64_t)objectId + 5;
    *packet << (uint32_t)0x70B79711;

    //datapad
    *packet << (uint16_t)0;
    *packet << (uint32_t)4;
    *packet << (uint64_t)objectId + 3;
    *packet << (uint32_t)0x73BA5001;

    //inventory
    *packet << (uint16_t)0;
    *packet << (uint32_t)4;
    *packet << (uint64_t)objectId + 1;
    *packet << (uint32_t)SWGCRC("object/tangible/inventory/shared_character_inventory.iff");

    //bank
    *packet << (uint16_t)0;
    *packet << (uint32_t)4;
    *packet << (uint64_t)objectId + 4;
    *packet << (uint32_t)0x70FD1394;

    //mission bag
    *packet << (uint16_t)0;
    *packet << (uint32_t)4;
    *packet << (uint64_t)objectId + 2;
    *packet << (uint32_t)0x3D7F6F9F;

    //hair
    *packet << (uint16_t)0;
    *packet << (uint32_t)4;
    *packet << (uint64_t)objectId + 8;
	*packet << (uint32_t)SWGCRC(hair.c_str());
	}
	else
	{
    *packet << (uint32_t)0; //List size for # of objects equipted
    *packet << (uint32_t)0; //176
	}
    //unknown short FIX ME
    *packet << (uint16_t)0;

    *packet << (uint8_t)0 << (uint16_t)0;


	return packet;
}

void Creo6Message::unserialize()
{
}

