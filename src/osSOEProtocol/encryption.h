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

#ifndef OPENSWG_SOEPROTOCOL_ENCRYPTION
#define OPENSWG_SOEPROTOCOL_ENCRYPTION

#include <gsNetwork/binarypacket.h>

namespace osSOEProtocol
{
    class Encryption
    {
    public:
        static void encrypt(std::shared_ptr<gsNetwork::BinaryPacket> packet, uint32_t crcSeed);
        static void crc(std::shared_ptr<gsNetwork::BinaryPacket> packet, uint32_t crcSeed);
        static void decrypt(std::shared_ptr<gsNetwork::BinaryPacket> packet, uint32_t crcSeed);
    };
}

#endif // OPENSWG_SOEPROTOCOL_ENCRYPTION

