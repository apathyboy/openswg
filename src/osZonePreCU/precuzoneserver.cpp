
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

#include "osZonePreCU/precuzoneserver.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/eventmanager.h>
#include <gsCore/processmanager.h>
#include <gsCore/sha1.h>
#include <gsServer/serverapplication.h>
#include <gsNetwork/events.h>
#include <gsNetwork/adminsocket.h>
#include <gsNetwork/clientsocket.h>
#include <gsNetwork/commsocket.h>
#include <gsNetwork/gamesocket.h>
#include <gsNetwork/pingsocket.h>
#include <gsServer/serverevents.h>
#include <gsCore/datastore.h>
#include <Sockets/StdoutLog.h>
#include <osZonePreCU/precuzoneservereventlistener.h>
#include <osSOEProtocol/soesocketfactory.h>
#include <osSOEProtocol/stationidentifiermessage.h>
#include <osSOEProtocol/accountversionmessage.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/characteroptionsmessage.h>
#include <osSOEProtocol/soelayermessages.h>
#include <osSOEProtocol/objectgrid.h>
#include <gsCore/datastore.h>

using namespace gsApplication;
using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;

PreCUZoneServer::PreCUZoneServer(std::string serverType, uint32_t serverId)
: ServerApplication(serverType, serverId)
{
}

PreCUZoneServer::~PreCUZoneServer()
{}

void PreCUZoneServer::initialize(const std::string& configFilename)
{
	m_sessionManager = GS_NEW SOESessionManager();
	m_galaxyManager = GS_NEW GalaxyManager();

    // Set our custom socket factory. This allows us to override the 
    // default client socket with the soe client socket which supports
    // the SOE decryption/decompression methods.
    setSocketFactory(GS_NEW SOESocketFactory(m_sessionManager));

    ServerApplication::initialize(configFilename);

	
    // Create containers for the configuration data.
    std::string dbHost;
    std::string dbName;
    std::string dbUser;
    std::string dbPassword;

    // Read the configuration data.
    m_config.readInto<std::string>(dbHost,     "station_dbhost");
    m_config.readInto<std::string>(dbName,     "station_dbname");
    m_config.readInto<std::string>(dbUser,     "station_dbuser");
    m_config.readInto<std::string>(dbPassword, "station_dbpass");

    // Test and store the database connection(s).
    try
    {
        // Establish connection to the datastore.
        Datastore::getStationDB().connect(dbName.c_str(),
                           dbHost.c_str(),
                           dbUser.c_str(),
                           dbPassword.c_str());

        if (! Datastore::getStationDB().connected())
        {
            LOG(ERROR) << "Unable to connect tot he datastore";
        }
    }
    catch (const mysqlpp::ConnectionFailed& er)
    {
        // handle any query errors.
        LOG(ERROR) << "ERROR: " << er.what();
        exit(EXIT_FAILURE);
    }
	
    // Read the configuration data.
    m_config.readInto<std::string>(dbHost,     "galaxy_dbhost");
    m_config.readInto<std::string>(dbName,     "galaxy_dbname");
    m_config.readInto<std::string>(dbUser,     "galaxy_dbuser");
    m_config.readInto<std::string>(dbPassword, "galaxy_dbpass");

    // Test and store the database connection(s).
    try
    {
        // Establish connection to the datastore.
        Datastore::getGalaxyDB().connect(dbName.c_str(),
                           dbHost.c_str(),
                           dbUser.c_str(),
                           dbPassword.c_str());

        if (! Datastore::getGalaxyDB().connected())
        {
            LOG(ERROR) << "Unable to connect tot he datastore";
        }
    }
    catch (const mysqlpp::ConnectionFailed& er)
    {
        // handle any query errors.
        LOG(ERROR) << "ERROR: " << er.what();
        exit(EXIT_FAILURE);
    }
	
	OpcodeFactory* opcodeFactory = GS_NEW OpcodeFactory;

	m_authManager = GS_NEW AuthManager();
	m_authManager->registerOpcodes(opcodeFactory);
	
	m_charCreationManager = GS_NEW CharacterCreationManager();
	m_charCreationManager->initialize();
	m_charCreationManager->registerOpcodes(opcodeFactory);	

	m_objectGrid = GS_NEW ObjectGrid;

	m_objectManager = GS_NEW ObjectManager(m_objectGrid);
	m_objectManager->initialize();
	m_objectManager->registerOpcodes(opcodeFactory);
	
	m_travelManager = GS_NEW TravelManager(m_objectGrid);
	m_travelManager->initialize();
	m_travelManager->registerOpcodes(opcodeFactory);     
	
	m_staticNpcManager = GS_NEW StaticNpcManager(m_objectGrid);
	m_staticNpcManager->initialize();
	m_staticNpcManager->registerOpcodes(opcodeFactory);

	m_sessionManager->setOpcodeFactory(opcodeFactory);

	// Register the basic events needed to run the server application.
	// Additional events or overrides can be performed from the concrete
	// application instance.	
	EventListenerPtr serverEventListener(GS_NEW PreCUZoneServerEventListener(this));
	PreCUZoneServerEventListener::registerEvents(serverEventListener);

    m_processManager->attach(ProcessPtr(m_sessionManager));
    m_processManager->attach(ProcessPtr(m_galaxyManager));
    m_processManager->attach(ProcessPtr(m_objectManager));
    m_processManager->attach(ProcessPtr(m_travelManager));
    m_processManager->attach(ProcessPtr(m_staticNpcManager));


    printf("\n<Ctrl-C> to exit ...\n\n" );
}

