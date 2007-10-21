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

#include <gsCore/log.h>
#include <gsCore/eventmanager.h>
#include <gsCore/processmanager.h>
#include <gsServer/serverapplication.h>
#include <gsServer/servereventlistener.h>
#include <gsServer/sessionmanager.h>
#include <gsNetwork/events.h>
#include <gsNetwork/adminsocket.h>
#include <gsNetwork/clientsocket.h>
#include <gsNetwork/commsocket.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/pingsocket.h>
#include <gsCore/datastore.h>
#include <Sockets/StdoutLog.h>

#include <zthread/ConcurrentExecutor.h>

#ifdef WIN32
//#include <omp.h>
#endif // WIN32

using namespace gsCore;
using namespace gsServer;
using namespace gsNetwork;

mysqlpp::Connection sStationDB;
mysqlpp::Connection sGalaxyDB;

ServerApplication::ServerApplication(std::string serverType, uint32 serverId)
: m_serverType(serverType)
, m_serverId(serverId)
, gsApplication::Application()
{
    m_socketListener = GS_NEW GameSocketListener;
}

ServerApplication::~ServerApplication()
{
	SAFE_DELETE(m_socketFactory);
}

void ServerApplication::shutdown()
{
	m_socketListener->toggleRunning();

	ZThread::Thread::sleep(1000);

	if (Datastore::getStationDB().connected())
		Datastore::getStationDB().close();

	if (Datastore::getGalaxyDB().connected())
		Datastore::getGalaxyDB().close();
}

void ServerApplication::initialize(const std::string& configFilename)
{
    Application::initialize(configFilename);
    
	// Register the basic events needed to run the server application.
	// Additional events or overrides can be performed from the concrete
	// application instance.
	EventListenerPtr eventLog(GS_NEW EventSnooper());
	EventSnooper::registerEvents(eventLog);
        
	EventListenerPtr packetLogger(GS_NEW PacketLogListener());
	PacketLogListener::registerEvents(packetLogger);

    // Create containers for the configuration data.
    std::string mainLog;
    std::string packetLog;
    uint16 adminSocket;
    uint16 clientSocket;
    uint16 commSocket;
    uint16 pingSocket;

    // Try loading the configuration before going further.
    try {
        // Load the configuration file and get some basic
        // configuration variables.
        m_config = ConfigFile(configFilename.c_str());
    } catch(...) {
        Log::getMainLog().error("Could not find configuration file %s.\n", configFilename);
		exit(EXIT_FAILURE);
    }

    // Read the configuration data.
    m_config.readInto<uint16>(adminSocket,  "admin_socket");
    m_config.readInto<uint16>(clientSocket, "client_socket");
    m_config.readInto<uint16>(commSocket,   "comm_socket");
    m_config.readInto<uint16>(pingSocket,   "ping_socket");

    printf(" *** Server hostname: %s\n", Utility::GetLocalHostname().c_str());
    printf(" *** Server IP: %s\n\n", Utility::GetLocalAddress().c_str());

    if (adminSocket != SOCKET_DISABLED)
    {
        addSocket(m_socketFactory->createGameSocket(gsNetwork::AdminSocket::gkName, *m_socketListener), adminSocket);
        Log::getMainLog().info("Listening for admin messages on port: [%i]", adminSocket);
    }

    if (clientSocket != SOCKET_DISABLED)
    {
        addSocket(m_socketFactory->createGameSocket(gsNetwork::ClientSocket::gkName, *m_socketListener), clientSocket);
        Log::getMainLog().info("Listening for client messages on port: [%i]", clientSocket);
    }

    if (commSocket != SOCKET_DISABLED)
    {
        addSocket(m_socketFactory->createGameSocket(gsNetwork::CommSocket::gkName, *m_socketListener), commSocket);
        Log::getMainLog().info("Listening for server messages on port: [%i]", commSocket);
    }

    if (pingSocket != SOCKET_DISABLED)
    {
        addSocket(m_socketFactory->createGameSocket(gsNetwork::PingSocket::gkName, *m_socketListener), pingSocket);
        Log::getMainLog().info("Listening for ping messages on port: [%i]", pingSocket);
    }
}

void ServerApplication::setSocketFactory(GameSocketFactory* factory)
{
    m_socketFactory = factory;
}

void ServerApplication::addSocket(GameSocket* socket, uint16 port)
{
    if (socket->Bind(port))
    {
        Log::getMainLog().error("Add Socket Failed");
        return;
    }

    m_socketListener->Add(socket);
}

void ServerApplication::startNetwork()
{
    m_socketListener->toggleRunning();

    ZThread::ConcurrentExecutor e;
    e.execute(m_socketListener);
}

void ServerApplication::run()
{
	startNetwork();

	Application::run();
}

void ServerApplication::tick(uint64 updateTimestamp)
{
    if (isRunning())
    {
		if (updateTimestamp - m_lastUpdateTimestamp > 25)
		{
		    uint64 deltaTimestamp = (updateTimestamp - m_lastUpdateTimestamp);
	        m_lastUpdateTimestamp = updateTimestamp;
            
            m_eventManager->tick(updateTimestamp);            
            m_processManager->tick(updateTimestamp);
		}
    }
}

