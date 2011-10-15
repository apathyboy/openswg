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

#include "osSOEProtocol/galaxymanager.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsServer/serverevents.h>
#include <osSOEProtocol/galaxymanagerlistener.h>
#include <gsCore/datastore.h>

using namespace gsCore;
using namespace gsServer;
using namespace osSOEProtocol;

GalaxyCharacter::GalaxyCharacter()
: m_firstname(NULL)
, m_surname(NULL)
, m_model(NULL)
, m_zoneId(NULL)
, m_objectId(NULL)
, m_characterId(NULL)
{}
GalaxyCharacter::GalaxyCharacter(std::string firstname, std::string surname, std::string model,
			uint64_t zoneId, uint64_t objectId, uint64_t characterId)
: m_firstname(firstname)
, m_surname(surname)
, m_model(model)
, m_zoneId(zoneId)
, m_objectId(objectId)
, m_characterId(characterId)
{}

std::string GalaxyCharacter::getFullName()
{
    if ((m_surname.length() != 0) && (m_firstname.length() != 0))
        return m_firstname + " " + m_surname;
    else if (m_firstname.length() != 0)
        return (std::string)m_firstname;
    else
        return (std::string)"";
}

GalaxyCluster::GalaxyCluster()
: m_id(NULL)
, m_version(NULL)
, m_name(NULL)
, m_status(SERVER_OFFLINE)
, m_maxCapacity(3000)
{}

GalaxyCluster::GalaxyCluster(uint32_t id, uint32_t version, std::string name, uint32_t maxCapacity, uint32_t status)
: m_id(id)
, m_version(version)
, m_name(name)
, m_status(status)
, m_maxCapacity(maxCapacity)
{}
		
uint32_t GalaxyCluster::getPopulation()
{
	uint32_t population = 0;

	for (std::list<GalaxyServer*>::iterator i = m_connectionServers.begin();
		i != m_connectionServers.end(); ++i)
	{
		population += (*i)->getPopulation();
	}

	return population;
}

GalaxyServer::GalaxyServer()
: m_id(NULL)
, m_serverType(CONNECTION_SERVER)
, m_serverAddress(NULL)
, m_adminPort(NULL)
, m_clientPort(NULL)
, m_commPort(NULL)
, m_pingPort(NULL)
, m_population(0)
, m_serverStatus(SERVER_OFFLINE)
{}

GalaxyServer::GalaxyServer(uint32_t id, GalaxyCluster* galaxy, uint32_t serverType, std::string serverAddress,
			uint16_t adminPort, uint16_t clientPort, uint16_t commPort, uint16_t pingPort,
			uint32_t population, uint32_t serverStatus)
: m_id(id)
, m_galaxy(galaxy)
, m_serverType(serverType)
, m_serverAddress(serverAddress)
, m_adminPort(adminPort)
, m_clientPort(clientPort)
, m_commPort(commPort)
, m_pingPort(pingPort)
, m_population(population)
, m_serverStatus(serverStatus)
{}

GalaxyManager::GalaxyManager()
: Process(PROC_GALAXY)
{}

GalaxyManager::~GalaxyManager()
{
	
}

void GalaxyManager::update(const uint64_t updateTimestamp)
{
	Process::update(updateTimestamp);

	// Every 5 minutes call the following:
	// m_galaxies = getGalaxyList();
}

void GalaxyManager::initialize()
{
    EventListenerPtr listener (GS_NEW GalaxyManagerListener(this));
	safeAddListener(listener, EventType(Event_AccountAuthenticated::gkName));
	
	m_galaxies = getGalaxyList();
}

GalaxyCluster* GalaxyManager::getGalaxy(uint32_t galaxyId)
{
	GalaxyCluster* galaxy;
	for(std::list<GalaxyCluster*>::iterator i = m_galaxies.begin();
		i != m_galaxies.end(); ++i)
	{
		if ((*i)->getGalaxyId() == galaxyId)
		{
			galaxy = (*i);
		}
	}
	return galaxy;
}

GalaxyServer* GalaxyManager::getConnectionServer(uint32_t galaxyId)
{
	GalaxyServer* connectionServer;

    try
    {
		mysqlpp::Query q = Datastore::getStationDB().query();

        q << "SELECT * FROM servers WHERE type = " << CONNECTION_SERVER
          << " AND galaxy_id = " << galaxyId
          << " ORDER BY population LIMIT 1";

        mysqlpp::StoreQueryResult result = q.store();

        if (result)
        {
			connectionServer = GS_NEW GalaxyServer
				((uint32_t)result[0]["id"],
				 getGalaxy(galaxyId),
				 (uint32_t)result[0]["type"],
				 (std::string)result[0]["address"],
				 (uint16_t)result[0]["admin_port"],
				 (uint16_t)result[0]["client_port"],
				 (uint16_t)result[0]["comm_port"],
				 (uint16_t)result[0]["ping_port"],
				 (uint32_t)result[0]["population"],
				 (uint32_t)result[0]["status"]);
        }

        else
        {
            LOG(ERROR) << "Failed to select connection server list";
        }
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR" << er.what();
	}

	return connectionServer;
}

std::list<GalaxyCluster*> GalaxyManager::getGalaxyList()
{
	std::list<GalaxyCluster*> galaxies;
    try
    {
        mysqlpp::Query q = Datastore::getStationDB().query();

        q << "SELECT * FROM galaxies";

        mysqlpp::StoreQueryResult result = q.store();

        if (result)
        {
            std::for_each(begin(result), end(result), [&galaxies] (const mysqlpp::Row& row) 
            {                
                GalaxyCluster* galaxy = GS_NEW GalaxyCluster
					((uint32_t)row["id"],
					 (uint32_t)row["version"],
					 (std::string)row["name"],
					 (uint32_t)row["max_capacity"],
					 (uint32_t)row["status"]);

                galaxies.push_back(galaxy);
            });
        }
        else
        {
            LOG(ERROR) << "Failed to select galaxy list";
        }
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR" << er.what();
	}

	return galaxies;
}

std::list<GalaxyServer*> GalaxyManager::getConnectionServerList(uint32_t galaxyId)
{
	std::list<GalaxyServer*> connectionServers;
	
    try
    {
		mysqlpp::Query q = Datastore::getStationDB().query();

        q << "SELECT * FROM servers WHERE type = " << CONNECTION_SERVER
          << " AND galaxy_id = " << galaxyId
          << " ORDER BY population";

        mysqlpp::StoreQueryResult result = q.store();

        if (result)
        {            
            std::for_each(begin(result), end(result), [this, galaxyId, &connectionServers] (const mysqlpp::Row& row) 
            {   
				GalaxyServer* connectionServer = GS_NEW GalaxyServer
					((uint32_t)row["id"],
					 getGalaxy(galaxyId),
					 (uint32_t)row["type"],
					 (std::string)row["address"],
					 (uint16_t)row["admin_port"],
					 (uint16_t)row["client_port"],
					 (uint16_t)row["comm_port"],
					 (uint16_t)row["ping_port"],
					 (uint32_t)row["population"],
					 (uint32_t)row["status"]);

				connectionServers.push_back(connectionServer);
            });
        }                    
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR" << er.what();
	}
	
	return connectionServers;
}

std::list<GalaxyServer*> GalaxyManager::getConnectionServerList()
{
	std::list<GalaxyServer*> connectionServers;

	for(std::list<GalaxyCluster*>::iterator i = m_galaxies.begin();
		i != m_galaxies.end(); ++i)
	{
		GalaxyServer* server = getConnectionServer((*i)->getGalaxyId());
		connectionServers.push_back(server);
	}

	return connectionServers;
}

std::list<GalaxyCharacter*> GalaxyManager::getCharacterList(uint32_t accountId)
{
	std::list<GalaxyCharacter*> characters;
        
    try
    {
        mysqlpp::Query q = Datastore::getStationDB().query();

        q << "SELECT characters.id, "
          << "       characters.account_id, "
          << "       characters.zone_id, "
		  << "		 characters.object_id, "
          << "       characters.firstname, "
          << "       characters.surname, "
          << "       characters.model "
          << "FROM characters "
          << "WHERE characters.account_id = " << accountId;

        mysqlpp::StoreQueryResult result = q.store();

        if (result)
        {      
            std::for_each(begin(result), end(result), [&characters] (const mysqlpp::Row& row) 
            {  
				GalaxyCharacter* character = GS_NEW GalaxyCharacter
					((std::string)row["firstname"],
					 (std::string)row["surname"],
					 (std::string)row["model"],
					 (uint64_t)row["zone_id"],
					 (uint64_t)row["object_id"],
					 (uint64_t)row["id"]);

				characters.push_back(character);
            });
        }                    
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR" << er.what();
	}

	return characters;
}
