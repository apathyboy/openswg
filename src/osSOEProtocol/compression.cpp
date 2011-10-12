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
#include <osSOEProtocol/compression.h>
#include <gsCore/macros.h>

using namespace gsNetwork;
using namespace osSOEProtocol;

void Compression::compress(gsNetwork::BinaryPacketPtr packet)
{
    char* data = packet->getData();
    uint32_t length = packet->getLength();

    char* tmp = new char[length];
    memcpy(tmp, data, length);

    data = tmp;

    Compress(&data, (uint16_t*)&length, 1);

    // Clear the current data in the packet and add the processed
    // data back in.
    packet->clear();
    for (uint32_t i = 0; i < length; ++i)
        packet->append<char>(data[i]);
}

void Compression::decompress(gsNetwork::BinaryPacketPtr packet)
{
    char* data = packet->getData();
    uint32_t length = packet->getLength();

    bool decompressed = false;
    if (data[2] == 'x' || data[1] == 'x')
    {
        data = Decompress(data, (uint16_t &)length);
        decompressed = true;
    }

    packet->clear();    
    for (uint32_t i = 0; i < length; ++i)
        packet->append<char>(data[i]);

    if (decompressed)
        SAFE_DELETE_ARRAY(data);
}

