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

#include <osSOEProtocol/charactercreationrequest.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

CharacterCreationRequest::CharacterCreationRequest()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

CharacterCreationRequest::CharacterCreationRequest(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

CharacterCreationRequest::~CharacterCreationRequest()
{}

BinaryPacketPtr CharacterCreationRequest::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

	return packet;
}

void CharacterCreationRequest::unserialize()
{
	appearance = m_serializedData->read<std::string>();
	fullname = m_serializedData->read<std::wstring>();

    std::string split(fullname.begin(), fullname.end());

    if (split.length())
    {
        uint16 i = split.find(" ");

        if (i < split.length())
        {
            firstname = split.substr(0, i);
            surname = split.substr(i+1);
        }
        else
            firstname = split;
    }

    race = m_serializedData->read<std::string>();
	
    if (race.length())
    {
        uint16 i = race.find("player/");
		
        race.replace(i, 7, "player/shared_");
		
		category = std::string("species");

		type = race.substr(race.find_first_of("_")+1, race.find_last_of("_")-(race.find_first_of("_")+1));
    }
    
    startingLocation = m_serializedData->read<std::string>();    
    hair = m_serializedData->read<std::string>();

    if (hair.length())
    {
        uint16 i = hair.find("hair_");
		hair.replace(i, 5, "shared_hair_");
	}

	hairData = m_serializedData->read<std::string>();
    profession = m_serializedData->read<std::string>();

    m_serializedData->read<uint8>(); // buffer byte, not used
    
    scale = m_serializedData->read<float>();
    
    biography = m_serializedData->read<std::wstring>();
	tutorial = m_serializedData->read<uint8>();
}

