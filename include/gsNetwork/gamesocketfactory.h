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

#ifndef GALAXY_NETWORK_GAMESOCKETFACTORY
#define GALAXY_NETWORK_GAMESOCKETFACTORY

#include <gsNetwork/export.h>

#include <Sockets/SocketHandler.h>

#include <string>

namespace gsNetwork
{
    class GameSocket;
    class GS_NETWORK_EXPORT GameSocketFactory
    {
    public:
        GameSocketFactory();

    public:
        GameSocket* createGameSocket(const std::string type, ISocketHandler &h);

    protected:
        virtual GameSocket* createAdminSocket(ISocketHandler &h);
        virtual GameSocket* createClientSocket(ISocketHandler &h);
        virtual GameSocket* createCommSocket(ISocketHandler &h);
        virtual GameSocket* createPingSocket(ISocketHandler &h);

    };
}

#endif // GALAXY_NETWORK_GAMESOCKETFACTORY

