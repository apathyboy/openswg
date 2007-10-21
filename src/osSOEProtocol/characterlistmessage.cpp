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

CharacterListMessage::CharacterListMessage(BinaryPacketPtr packet)
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

BinaryPacketPtr CharacterListMessage::serialize()
{
    BinaryPacketPtr packet(GS_NEW BinaryPacket);
    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)2;
    *packet << (uint32)SMSG_CHAR_LIST;
    
    *packet << (uint32)characters.size(); // Character count

	for (std::list<GalaxyCharacter*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        *packet << (uint32)(*i)->getFullName().length();

        for (uint j = 0; j < (*i)->getFullName().length(); ++j)
			*packet << (unicode)(*i)->getFullName().c_str()[j];

        *packet << (uint32)(*i)->getModelCrc();
        *packet << (uint64)(*i)->getCharacterId();
        *packet << (uint32)(*i)->getZoneId();
        *packet << (uint32)1;
    }

    // Add character list data

    *packet << (uint8)0;
    *packet << (uint16)0;

	return packet;
}

void CharacterListMessage::unserialize()
{
}

