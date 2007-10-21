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

    *packet << (uint16)SOE_CHL_DATA_A;
    *packet << (uint16)htons(getSequence());
    *packet << (uint16)5;
    *packet << (uint32)AMSG_INT_PACKET;
    *packet << (uint32)0x0000000b;
    *packet << (uint32)0x00000147;
    *packet << (uint64)objectId;
    *packet << (uint32)0;

    *packet << (uint64)targetId;
    *packet << (uint64)objectId;

    *packet << (uint32)radialMap.size();

    uint count = 1;
    for (RadialMenuMap::reverse_iterator i = radialMap.rbegin(); i != radialMap.rend(); ++i)
    {
        RadialOption option = (*i).second;

        *packet << (uint8)option.index;
        *packet << (uint8)option.parentIndex;
        *packet << (uint8)option.id;

        if (option.id == 20)
        {
            *packet << (uint8)3;
        }
        else
        {
            *packet << (uint8)1;
        }

        *packet << (uint32)0;
        ++count;
    }

    *packet << (uint8)1;

    *packet << (uint8)0 << (uint16)0;
	return packet;
}

void RadialResponseMessage::unserialize()
{
}

