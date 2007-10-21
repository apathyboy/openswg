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

#include <osSOEProtocol/tano6message.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

Tano6Message::Tano6Message()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

Tano6Message::Tano6Message(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

Tano6Message::~Tano6Message()
{}

BinaryPacketPtr Tano6Message::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    // Send TANO 6
    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)SMSG_OBJ_UPDATE;
    *packet << (uint64)objectId;

    // Object Packet Type (CREO3)
    *packet << "ONAT" << (uint8)6;
    *packet << (uint32)15;//+type.length()+typeDetail.length();

    *packet << (uint16)3;
    *packet << (uint32)61;

    *packet << (uint16)0;//type.length();
    //if (type.length()>0)
    //    packet->append<std::string>(type);

    *packet << (uint32)0;

    *packet << (uint16)0;//typeDetail.length();
    //if (typeDetail.length()>0)
    //    packet->append<std::string>(typeDetail);

    *packet << (uint8)1;

    *packet << (uint8)0 << (uint16)0;

	return packet;
}

void Tano6Message::unserialize()
{
}

