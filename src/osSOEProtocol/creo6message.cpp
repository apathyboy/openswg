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

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)SMSG_OBJ_UPDATE;
    *packet << (uint64)objectId;

    // Object Packet Type (CREO3)
    *packet << (uint32)0x4352454F;
    *packet << (uint8)6;

    *packet << (uint32)437+mood.length();
    *packet << (uint16)22;
    *packet << (uint32)0; // Defender update counter
    *packet << (uint64)0; // Current defender

    *packet << (uint16)0; // Con level

    *packet << (uint16)0; // Music/Dance type

    //Mood String
    *packet << (uint16)mood.length();
	packet->append<std::string>(mood);

    *packet << (uint64)objectId + 5; // weao id

    *packet << (uint64)0; // Group id

    //unknowns FIX ME s
    *packet << (uint64)0;
    *packet << (uint64)0;
    *packet << (uint32)0; //
    *packet << (uint64)0;
    *packet << (uint8)0; //I was told that this wasmood.
    *packet << (uint32)0; //one of these might be GILD ID.
    *packet << (uint32)0; //

    *packet << (uint32)9; // list size for each HAM section
    *packet << (uint32)9; // 

	*packet << (uint32)currentHealth;
	*packet << (uint32)currentStrength;
	*packet << (uint32)currentConstitution;
	*packet << (uint32)currentAction;
	*packet << (uint32)currentQuickness;
	*packet << (uint32)currentStamina;
	*packet << (uint32)currentMind;
	*packet << (uint32)currentFocus;
	*packet << (uint32)currentWillpower;

    *packet << (uint32)9; // list size for each HAM section
    *packet << (uint32)9; // 

	*packet << (uint32)maxHealth;
	*packet << (uint32)maxStrength;
	*packet << (uint32)maxConstitution;
	*packet << (uint32)maxAction;
	*packet << (uint32)maxQuickness;
	*packet << (uint32)maxStamina;
	*packet << (uint32)maxMind;
	*packet << (uint32)maxFocus;
	*packet << (uint32)maxWillpower;

	if (isPlayer)
	{
    //EQUIPTMENT LIST FIX ME LATER
    *packet << (uint32)6; //List size for # of objects equipted
    *packet << (uint32)6; //176

    //weapon
    *packet << (uint16)0;
    *packet << (uint32)4;
    *packet << (uint64)objectId + 5;
    *packet << (uint32)0x70B79711;

    //datapad
    *packet << (uint16)0;
    *packet << (uint32)4;
    *packet << (uint64)objectId + 3;
    *packet << (uint32)0x73BA5001;

    //inventory
    *packet << (uint16)0;
    *packet << (uint32)4;
    *packet << (uint64)objectId + 1;
    *packet << (uint32)SWGCRC("object/tangible/inventory/shared_character_inventory.iff");

    //bank
    *packet << (uint16)0;
    *packet << (uint32)4;
    *packet << (uint64)objectId + 4;
    *packet << (uint32)0x70FD1394;

    //mission bag
    *packet << (uint16)0;
    *packet << (uint32)4;
    *packet << (uint64)objectId + 2;
    *packet << (uint32)0x3D7F6F9F;

    //hair
    *packet << (uint16)0;
    *packet << (uint32)4;
    *packet << (uint64)objectId + 8;
	*packet << (uint32)SWGCRC(hair.c_str());
	}
	else
	{
    *packet << (uint32)0; //List size for # of objects equipted
    *packet << (uint32)0; //176
	}
    //unknown short FIX ME
    *packet << (uint16)0;

    *packet << (uint8)0 << (uint16)0;


	return packet;
}

void Creo6Message::unserialize()
{
}

