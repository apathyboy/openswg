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

#include <cstdint>
#include <memory>
#include <string>

#include <boost/asio/io_service.hpp>

namespace gsNetwork
{
    class UdpEventSocket;
    class GameSocketFactory
    {
    public:
        GameSocketFactory();

    public:
        std::shared_ptr<UdpEventSocket> createGameSocket(const std::string type, boost::asio::io_service &io_service, uint16_t port);

    protected:
        virtual std::shared_ptr<UdpEventSocket> createAdminSocket(boost::asio::io_service &io_service, uint16_t port);
        virtual std::shared_ptr<UdpEventSocket> createClientSocket(boost::asio::io_service &io_service, uint16_t port);
        virtual std::shared_ptr<UdpEventSocket> createCommSocket(boost::asio::io_service &io_service, uint16_t port);
        virtual std::shared_ptr<UdpEventSocket> createPingSocket(boost::asio::io_service &io_service, uint16_t port);

    };
}

#endif // GALAXY_NETWORK_GAMESOCKETFACTORY

