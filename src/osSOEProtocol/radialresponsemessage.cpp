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

#include <osSOEProtocol/radialresponsemessage.h>
#include <osSOEProtocol/opcodes.h>
#include <gsNetwork/gamesocket.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

RadialResponseMessage::RadialResponseMessage()
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
}

RadialResponseMessage::RadialResponseMessage(BinaryPacketPtr packet)
: NetworkMessage()
{
	setPriority(0);
	setResend(true);
	setEncrypt(true);
	setCrc(true);
	m_serializedData = packet;
}

RadialResponseMessage::~RadialResponseMessage()
{}

BinaryPacketPtr RadialResponseMessage::serialize()
{
    BinaryPacketPtr packet(new BinaryPacket);

    *packet << (uint16_t)SOE_CHL_DATA_A;
    *packet << (uint16_t)htons(getSequence());
    *packet << (uint16_t)5;
    *packet << (uint32_t)AMSG_INT_PACKET;
    *packet << (uint32_t)0x0000000b;
    *packet << (uint32_t)0x00000147;
    *packet << (uint64_t)objectId;
    *packet << (uint32_t)0;

    *packet << (uint64_t)targetId;
    *packet << (uint64_t)objectId;

    *packet << (uint32_t)radialMap.size();

    uint32_t count = 1;
    for (RadialMenuMap::reverse_iterator i = radialMap.rbegin(); i != radialMap.rend(); ++i)
    {
        RadialOption option = (*i).second;

        *packet << (uint8_t)option.index;
        *packet << (uint8_t)option.parentIndex;
        *packet << (uint8_t)option.id;

        if (option.id == 20)
        {
            *packet << (uint8_t)3;
        }
        else
        {
            *packet << (uint8_t)1;
        }

        *packet << (uint32_t)0;
        ++count;
    }

    *packet << (uint8_t)1;

    *packet << (uint8_t)0 << (uint16_t)0;
	return packet;
}

void RadialResponseMessage::unserialize()
{
}

