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

#include <osSOEProtocol/characterlistmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

CharacterListMessage::CharacterListMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

CharacterListMessage::CharacterListMessage(std::shared_ptr<BinaryPacket> packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

CharacterListMessage::~CharacterListMessage()
{}

std::shared_ptr<BinaryPacket> CharacterListMessage::serialize()
{
    std::shared_ptr<BinaryPacket> packet(GS_NEW BinaryPacket);
    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)2;
    *packet << (uint32_t)SMSG_CHAR_LIST;
    
    *packet << (uint32_t)characters.size(); // Character count

	for (std::list<GalaxyCharacter*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        *packet << (uint32_t)(*i)->getFullName().length();

        for (uint32_t j = 0; j < (*i)->getFullName().length(); ++j)
			*packet << (uint16_t)(*i)->getFullName().c_str()[j];

        *packet << (uint32_t)(*i)->getModelCrc();
        *packet << (uint64_t)(*i)->getCharacterId();
        *packet << (uint32_t)(*i)->getZoneId();
        *packet << (uint32_t)1;
    }

    // Add character list data

    *packet << (uint8_t)0;
    *packet << (uint16_t)0;

	return packet;
}

void CharacterListMessage::unserialize()
{
}

