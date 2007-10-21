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

#include <osSOEProtocol/tano3message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Tano3Message::Tano3Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Tano3Message::Tano3Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Tano3Message::~Tano3Message()
{}

BinaryPacketPtr Tano3Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)SMSG_OBJ_UPDATE;
    *packet << (uint64)objectId;

    // Object Packet Type (CREO3)
    *packet << "ONAT" << (uint8)3;
    *packet << (uint32)49+((customName.length()*2) + category.length() + type.length() + color.length());

    *packet << (uint16)11;
    *packet << (uint32)0;
    *packet << (uint16)category.length();
    packet->append<std::string>(category);

    *packet << (uint32)0;
    *packet << (uint16)type.length();
    packet->append<std::string>(type);

    *packet << (uint32)customName.length();
    for (uint i = 0; i < customName.length(); ++i)
        *packet << (unicode)customName.c_str()[i];

    *packet << (uint32)1;
    *packet << (uint16)color.length();

    if (color.length() > 0)
        packet->append<std::string>(color);

    *packet << (uint64)0;                                     //Unknown
    *packet << (uint64)768;                                   //Unknown
    *packet << (uint64)0;                                     //Unknown
    *packet << (uint8)1;                                      //Unknown

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Tano3Message::unserialize()
{
}

