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

#include <osSOEProtocol/soepackettools.h>
#include <osSOEProtocol/encryption.h>
#include <osSOEProtocol/opcodes.h>

#include <Sockets/Utility.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

void Encryption::crc(std::shared_ptr<gsNetwork::BinaryPacket> packet, uint32_t crcSeed)
{
    char* data = packet->getData();
    uint32_t length = packet->getLength();

    AppendCRC(data, (uint16_t)length, crcSeed);

    packet->clear();
    for (uint32_t i = 0; i < length; ++i)
        packet->append<char>(data[i]);
}
        
void Encryption::encrypt(std::shared_ptr<gsNetwork::BinaryPacket> packet, uint32_t crcSeed)
{
    char* data = packet->getData();
    uint32_t length = packet->getLength();

    Encrypt(data, (uint16_t)length, crcSeed);

    packet->clear();
    for (uint32_t i = 0; i < length; ++i)
        packet->append<char>(data[i]);	
}
        
void Encryption::decrypt(std::shared_ptr<gsNetwork::BinaryPacket> packet, uint32_t crcSeed)
{
    char* data = packet->getData();
    uint32_t length = packet->getLength();

    uint16_t group = ntohs(data[1]);
    uint32_t seed = crcSeed;

    if (group == SOE_MULTI_PKT)
    {
        if (CrcTest(data, (uint16_t)length, seed))
            Decrypt(data, (uint16_t)length, seed);
    }

    else if(group == SOE_CHL_DATA_A || group == SOE_DATA_FRAG_A || group == SOE_PING ||
            group == SOE_NET_STATUS_REQ || group == SOE_ACK_A || group == SOE_DISCONNECT ||
            group == SOE_OUT_ORDER_PKT_A)
    {
        Decrypt(data, (uint16_t)length, seed);
    }

	else if(data[0] == 0x05)
	{
        Decrypt(data, (uint16_t)length, seed, false);
	}

    packet->clear();
    for (uint32_t i = 0; i < length; ++i)
        packet->append<char>(data[i]);
}

