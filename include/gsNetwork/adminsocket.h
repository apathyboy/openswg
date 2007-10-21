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

#ifndef GALAXY_NETWORK_ADMINSOCKET
#define GALAXY_NETWORK_ADMINSOCKET

#include <gsCore/globals.h>
#include <gsCore/macros.h>

#include <gsNetwork/gamesocket.h>
#include <gsNetwork/export.h>

namespace gsNetwork
{
    class GS_NETWORK_EXPORT AdminSocket : public GameSocket
    {
    public:
        AdminSocket(ISocketHandler&);

        static char const * const gkName;

    public:
        virtual boost::optional<BinaryPacketPtr> processPacketData(BinaryPacketPtr packet, NetworkAddressPtr address);
    };
}

#endif // GALAXY_NETWORK_ADMINSOCKET

