/**
 * Galaxy Open-Source Massively Multiplayer Game Simulation Engine
 * Copyright (C) 2011 OpenSWG Team <http://openswg.org>
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

#ifndef GALAXY_SERVER_SERVERAPPLICATION
#define GALAXY_SERVER_SERVERAPPLICATION

#include <cstdint>

#include <memory>
#include <string>
#include <vector>

#include <boost/asio/io_service.hpp>

#include "gsApplication/application.h"

namespace gsNetwork
{
    class UdpEventSocket;
    class GameSocketListener;
    class GameSocketFactory;
};

namespace gsServer
{
    class ServerApplication : public gsApplication::Application
    {
    public:
		ServerApplication(std::string serverType, uint32_t serverId);
		~ServerApplication();
        
        virtual void initialize(const std::string& configFilename);
		virtual void shutdown();
        virtual void startNetwork();
		virtual void run();

        gsNetwork::GameSocketListener* getSocketListener() { return m_socketListener; }

        void setSocketFactory(gsNetwork::GameSocketFactory* factory);

        virtual void tick(uint64_t updateTimestamp);

		std::string getServerType() {return m_serverType;}
		uint32_t getServerId() {return m_serverId;}

    protected:
        boost::asio::io_service io_service_;
        boost::asio::io_service::work work_;
        std::vector<std::shared_ptr<gsNetwork::UdpEventSocket>> sockets_;

        gsNetwork::GameSocketListener* m_socketListener;
        gsNetwork::GameSocketFactory* m_socketFactory;

		std::string m_serverType;
		
        uint32_t m_serverId;
    };
}

#endif // GALAXY_SERVER_SERVERAPPLICATION

