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

#include <osSOEProtocol/stationidentifiermessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

StationIdentifierMessage::StationIdentifierMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

StationIdentifierMessage::StationIdentifierMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

StationIdentifierMessage::~StationIdentifierMessage()
{}

BinaryPacketPtr StationIdentifierMessage::serialize()
{
    unsigned const char station_head[56] = { //june 05
        0x20, 0x00,
        0x00, 0x00, 0x15, 0x00,	0x00, 0x00, 0x0E, 0xD6,
        0x93, 0xDE, 0xD2, 0xEF,	0xBF, 0x8E, 0xA1, 0xAC,
        0xD2, 0xEE, 0x4C, 0x55,	0xBE, 0x30, 0x5F, 0xBE,
        0x23, 0x0D, 0xB4, 0xAB,	0x58, 0xF9, 0x62, 0x69,
        0x79, 0x67, 0xE8, 0x10,	0x6E, 0xD3, 0x86, 0x9B,
        0x3A, 0x4A, 0x1A, 0x72,	0xA1, 0xFA, 0x8F, 0x96,
        0xFF, 0x9F, 0xA5, 0x62,	0x5A, 0x29
    };

    BinaryPacketPtr packet(new BinaryPacket);
    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)4;
    *packet << (uint32_t)SMSG_STATION_SESSION;
    *packet << (uint32_t)60;

    for (int i=0; i < 56; ++i)
        *packet << station_head[i];

    *packet << session->getAccountId();
    *packet << (uint32_t)0;
    *packet << (uint16_t)session->getUsername().length();
    packet->append<std::string>(session->getUsername());
    *packet << (uint8_t)0;
    *packet << (uint16_t)0;

	return packet;
}

void StationIdentifierMessage::unserialize()
{
}

