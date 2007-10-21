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

#include <gsNetwork/adminsocket.h>
#include <gsNetwork/clientsocket.h>
#include <gsNetwork/commsocket.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/pingsocket.h>
#include <gsNetwork/gamesocketfactory.h>

using namespace gsNetwork;

GameSocketFactory::GameSocketFactory()
{}

GameSocket* GameSocketFactory::createGameSocket(const std::string type, ISocketHandler &h)
{
    GameSocket* socket;

    if (strcmp(type.c_str(), AdminSocket::gkName) == 0)
        socket = createAdminSocket(h);

    if (strcmp(type.c_str(), ClientSocket::gkName) == 0)
        socket = createClientSocket(h);

    if (strcmp(type.c_str(), CommSocket::gkName) == 0)
        socket = createCommSocket(h);
    
    if (strcmp(type.c_str(), PingSocket::gkName) == 0)
        socket = createPingSocket(h);

    return socket;
}

GameSocket* GameSocketFactory::createAdminSocket(ISocketHandler &h)
{
    AdminSocket* socket = GS_NEW AdminSocket(h);
    return dynamic_cast<GameSocket*>(socket);
}

GameSocket* GameSocketFactory::createClientSocket(ISocketHandler &h)
{
    ClientSocket* socket = GS_NEW ClientSocket(h);
    return dynamic_cast<GameSocket*>(socket);
}

GameSocket* GameSocketFactory::createCommSocket(ISocketHandler &h)
{
    CommSocket* socket = GS_NEW CommSocket(h);
    return dynamic_cast<GameSocket*>(socket);
}

GameSocket* GameSocketFactory::createPingSocket(ISocketHandler &h)
{
    PingSocket* socket = GS_NEW PingSocket(h);
    return dynamic_cast<GameSocket*>(socket);
}

