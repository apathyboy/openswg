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

#include <boost/asio.hpp>

#include <osSOEProtocol/opcodes.h>

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

Tano3Message::Tano3Message(std::shared_ptr<BinaryPacket> packet)
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

std::shared_ptr<BinaryPacket> Tano3Message::serialize()
{
    std::shared_ptr<BinaryPacket> packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)SMSG_OBJ_UPDATE;
    *packet << (uint64_t)objectId;

    // Object Packet Type (CREO3)
    *packet << "ONAT" << (uint8_t)3;
    *packet << (uint32_t)49+((customName.length()*2) + category.length() + type.length() + color.length());

    *packet << (uint16_t)11;
    *packet << (uint32_t)0;
    *packet << (uint16_t)category.length();
    packet->append<std::string>(category);

    *packet << (uint32_t)0;
    *packet << (uint16_t)type.length();
    packet->append<std::string>(type);

    *packet << (uint32_t)customName.length();
    for (uint32_t i = 0; i < customName.length(); ++i)
        *packet << (uint16_t)customName.c_str()[i];

    *packet << (uint32_t)1;
    *packet << (uint16_t)color.length();

    if (color.length() > 0)
        packet->append<std::string>(color);

    *packet << (uint64_t)0;                                     //Unknown
    *packet << (uint64_t)768;                                   //Unknown
    *packet << (uint64_t)0;                                     //Unknown
    *packet << (uint8_t)1;                                      //Unknown

    *packet << (uint8_t)0 << (uint16_t)0;

	return packet;
}

void Tano3Message::unserialize()
{
}

