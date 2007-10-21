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

#ifndef GALAXY_SERVER_SERVERAPPLICATION
#define GALAXY_SERVER_SERVERAPPLICATION

#include <gsApplication/application.h>
#include <gsCore/macros.h>
#include <gsCore/types.h>
#include <gsServer/export.h>
#include <gsCore/types.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/gamesocketfactory.h>
#include <gsNetwork/gamesocketlistener.h>

#include <Sockets/SocketHandler.h>

namespace gsServer
{
    class GS_SERVER_EXPORT ServerApplication : public gsApplication::Application
    {
    public:
		ServerApplication(std::string serverType, uint32 serverId);
		~ServerApplication();
        
        virtual void initialize(const std::string& configFilename);
		virtual void shutdown();
        virtual void startNetwork();
		virtual void run();

        void addSocket(gsNetwork::GameSocket* socket, uint16 port);
        gsNetwork::GameSocketListener* getSocketListener() { return m_socketListener; }

        void setSocketFactory(gsNetwork::GameSocketFactory* factory);

        virtual void tick(uint64 updateTimestamp);

		std::string getServerType() {return m_serverType;}
		uint32 getServerId() {return m_serverId;}

    protected:
        gsNetwork::GameSocketListener* m_socketListener;
        gsNetwork::GameSocketFactory* m_socketFactory;
		std::string m_serverType;
		uint32 m_serverId;
    };
}

#endif // GALAXY_SERVER_SERVERAPPLICATION

