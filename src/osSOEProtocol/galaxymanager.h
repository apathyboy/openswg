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

#ifndef OPENSWG_SOEPROTOCOL_GALAXYMANAGER
#define OPENSWG_SOEPROTOCOL_GALAXYMANAGER

#include <cstdint>
#include <list>
#include <map>
#include <string>

#include <osSOEProtocol/soepackettools.h>
#include <gsCore/process.h>
#include <gsCore/macros.h>
#include <gsCore/globals.h>

namespace osSOEProtocol
{
	enum GalaxyTypes
	{
		SWG_PRECU = 0,
		SWG_PRECU_PRE9,
		SWG_PRECU_13_1,
		SWG_PRECU_14_1,
		SWG_CU,
		SWG_NGE
	};

	enum ServerTypes
	{
		CONNECTION_SERVER = 0,
		CHARACTER_SERVER,
		LOGIN_SERVER,
		ZONE_SERVER,
		CHAT_SERVER
	};

	enum ServerStatusTypes
	{
		SERVER_OFFLINE = 0,
		SERVER_LOADING,
		SERVER_ONLINE
	};


	class GalaxyCharacter;
	class GalaxyServer;
	class GalaxyCluster
	{
	public:
		GalaxyCluster();
		GalaxyCluster(uint32_t id, uint32_t version, std::string name, uint32_t maxCapacity, uint32_t status);

		uint32_t getGalaxyId() { return m_id; }
		int getVersion() { return m_version; }
		std::string getGalaxyName() { return m_name; }
		int getGalaxyStatus() { return m_status; }

		uint32_t getPopulation();
		uint32_t getMaxCapacity() { return m_maxCapacity; }

	protected:
		uint32_t m_id;
		std::list<GalaxyServer*> m_connectionServers;
		int m_version; 
		std::string m_name;
		int m_status;
		uint32_t m_population;
		uint32_t m_maxCapacity;
	};

	class GalaxyCharacter
	{
	public:
		GalaxyCharacter();
		GalaxyCharacter(std::string firstname, std::string surname, std::string model,
			uint64_t zoneId, uint64_t objectId, uint64_t characterId);

		std::string getFullName();
		std::string getFirstname() { return m_firstname; }
		std::string getSurname() { return m_surname; }

		uint32_t getModelCrc() {
			uint16_t i = m_model.find("player/shared_");		
			m_model.replace(i, 14, "player/");
			return SWGCRC(m_model.c_str()); 
		}
		uint64_t getZoneId() { return m_zoneId; }
		uint64_t getObjectId() { return m_objectId; }
		uint64_t getCharacterId() { return m_characterId; }

	public:
		uint64_t m_zoneId;
		uint64_t m_characterId;
		uint64_t m_objectId;
		std::string m_model;
		std::string m_firstname;
		std::string m_surname;
	};

	class GalaxyServer
	{
	public:
		GalaxyServer();
		GalaxyServer(uint32_t id, GalaxyCluster* galaxy, uint32_t serverType, std::string serverAddress,
			uint16_t adminPort, uint16_t clientPort, uint16_t commPort, uint16_t pingPort,
			uint32_t population, uint32_t serverStatus);

		uint32_t getServerId() { return m_id; }
		GalaxyCluster* getGalaxy() { return m_galaxy; }
		uint32_t getServerType() { return m_serverType; }
		std::string getServerAddress() { return m_serverAddress; }
		uint16_t getAdminPort() { return m_adminPort; }
		uint16_t getClientPort() { return m_clientPort; }
		uint16_t getCommPort() { return m_commPort; }
		uint16_t getPingPort() {return m_pingPort; }
		uint32_t getPopulation() { return m_population; }
		uint32_t getServerStatus() { return m_serverStatus; }

	protected:
		uint32_t m_id;
		GalaxyCluster* m_galaxy;
		uint32_t m_serverType;
		std::string m_serverAddress;
		uint16_t m_adminPort;
		uint16_t m_clientPort;
		uint16_t m_commPort;
		uint16_t m_pingPort;
		uint32_t m_population;
		uint32_t m_serverStatus;
	};

	class GalaxyManager : public gsCore::Process
	{
	public:
		GalaxyManager();
		virtual ~GalaxyManager();

	public:
        virtual void update(const uint64_t updateTimestamp);
        virtual void initialize();

		GalaxyCluster* getGalaxy(uint32_t galaxyId);
		std::list<GalaxyCluster*> getGalaxyList();
		std::list<GalaxyServer*> getConnectionServerList();
		std::list<GalaxyServer*> getConnectionServerList(uint32_t galaxyId);
		std::list<GalaxyCharacter*> getCharacterList(uint32_t accountId);
		GalaxyServer* getConnectionServer(uint32_t galaxyId);

	protected:
		std::list<GalaxyCluster*> m_galaxies;
		std::list<GalaxyServer*> m_connectionServers;
	};
}

#endif // OPENSWG_SOEPROTOCOL_GALAXYMANAGER