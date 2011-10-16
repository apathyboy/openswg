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

#include "gsNetwork/gamesocketfactory.h"

#include "gsNetwork/adminsocket.h"
#include "gsNetwork/clientsocket.h"
#include "gsNetwork/commsocket.h"
#include "gsNetwork/pingsocket.h"

using namespace gsNetwork;

GameSocketFactory::GameSocketFactory()
{}

std::shared_ptr<UdpEventSocket> GameSocketFactory::createGameSocket(const std::string type, boost::asio::io_service &io_service, uint16_t port)
{
    std::shared_ptr<UdpEventSocket> socket;

    if (strcmp(type.c_str(), AdminSocket::gkName) == 0)
        socket = createAdminSocket(io_service, port);

    if (strcmp(type.c_str(), ClientSocket::gkName) == 0)
        socket = createClientSocket(io_service, port);

    if (strcmp(type.c_str(), CommSocket::gkName) == 0)
        socket = createCommSocket(io_service, port);
    
    if (strcmp(type.c_str(), PingSocket::gkName) == 0)
        socket = createPingSocket(io_service, port);

    return socket;
}

std::shared_ptr<UdpEventSocket> GameSocketFactory::createAdminSocket(boost::asio::io_service &io_service, uint16_t port)
{
    return std::make_shared<AdminSocket>(io_service, port);
}

std::shared_ptr<UdpEventSocket> GameSocketFactory::createClientSocket(boost::asio::io_service &io_service, uint16_t port)
{
    return std::make_shared<ClientSocket>(io_service, port);
}

std::shared_ptr<UdpEventSocket> GameSocketFactory::createCommSocket(boost::asio::io_service &io_service, uint16_t port)
{
    return std::make_shared<CommSocket>(io_service, port);
}

std::shared_ptr<UdpEventSocket> GameSocketFactory::createPingSocket(boost::asio::io_service &io_service, uint16_t port)
{
    return std::make_shared<PingSocket>(io_service, port);
}

