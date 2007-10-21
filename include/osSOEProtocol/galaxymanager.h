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

#include <osSOEProtocol/export.h>
#include <osSOEProtocol/soepackettools.h>
#include <gsCore/process.h>
#include <gsCore/macros.h>
#include <gsCore/globals.h>
#include <string>
#include <list>
#include <map>

namespace osSOEProtocol
{
	enum OS_SOEPROTOCOL_EXPORT GalaxyTypes
	{
		SWG_PRECU = 0,
		SWG_PRECU_PRE9,
		SWG_PRECU_13_1,
		SWG_PRECU_14_1,
		SWG_CU,
		SWG_NGE
	};

	enum OS_SOEPROTOCOL_EXPORT ServerTypes
	{
		CONNECTION_SERVER = 0,
		CHARACTER_SERVER,
		LOGIN_SERVER,
		ZONE_SERVER,
		CHAT_SERVER
	};

	enum OS_SOEPROTOCOL_EXPORT ServerStatusTypes
	{
		SERVER_OFFLINE = 0,
		SERVER_LOADING,
		SERVER_ONLINE
	};


	class GalaxyCharacter;
	class GalaxyServer;
	class OS_SOEPROTOCOL_EXPORT GalaxyCluster
	{
	public:
		GalaxyCluster();
		GalaxyCluster(uint32 id, uint32 version, std::string name, uint32 maxCapacity, uint32 status);

		uint32 getGalaxyId() { return m_id; }
		int getVersion() { return m_version; }
		std::string getGalaxyName() { return m_name; }
		int getGalaxyStatus() { return m_status; }

		uint32 getPopulation();
		uint32 getMaxCapacity() { return m_maxCapacity; }

	protected:
		uint32 m_id;
		std::list<GalaxyServer*> m_connectionServers;
		int m_version; 
		std::string m_name;
		int m_status;
		uint32 m_population;
		uint32 m_maxCapacity;
	};

	class OS_SOEPROTOCOL_EXPORT GalaxyCharacter
	{
	public:
		GalaxyCharacter();
		GalaxyCharacter(std::string firstname, std::string surname, std::string model,
			uint64 zoneId, uint64 objectId, uint64 characterId);

		std::string getFullName();
		std::string getFirstname() { return m_firstname; }
		std::string getSurname() { return m_surname; }

		uint32 getModelCrc() {
			uint16 i = m_model.find("player/shared_");		
			m_model.replace(i, 14, "player/");
			return SWGCRC(m_model.c_str()); 
		}
		uint64 getZoneId() { return m_zoneId; }
		uint64 getObjectId() { return m_objectId; }
		uint64 getCharacterId() { return m_characterId; }

	public:
		uint64 m_zoneId;
		uint64 m_characterId;
		uint64 m_objectId;
		std::string m_model;
		std::string m_firstname;
		std::string m_surname;
	};

	class OS_SOEPROTOCOL_EXPORT GalaxyServer
	{
	public:
		GalaxyServer();
		GalaxyServer(uint32 id, GalaxyCluster* galaxy, uint serverType, std::string serverAddress,
			uint16 adminPort, uint16 clientPort, uint16 commPort, uint16 pingPort,
			uint32 population, uint serverStatus);

		uint32 getServerId() { return m_id; }
		GalaxyCluster* getGalaxy() { return m_galaxy; }
		uint getServerType() { return m_serverType; }
		std::string getServerAddress() { return m_serverAddress; }
		uint16 getAdminPort() { return m_adminPort; }
		uint16 getClientPort() { return m_clientPort; }
		uint16 getCommPort() { return m_commPort; }
		uint16 getPingPort() {return m_pingPort; }
		uint32 getPopulation() { return m_population; }
		uint getServerStatus() { return m_serverStatus; }

	protected:
		uint32 m_id;
		GalaxyCluster* m_galaxy;
		uint m_serverType;
		std::string m_serverAddress;
		uint16 m_adminPort;
		uint16 m_clientPort;
		uint16 m_commPort;
		uint16 m_pingPort;
		uint32 m_population;
		uint m_serverStatus;
	};

	class OS_SOEPROTOCOL_EXPORT GalaxyManager : public gsCore::Process
	{
	public:
		GalaxyManager();
		virtual ~GalaxyManager();

	public:
        virtual void update(const uint64 updateTimestamp);
        virtual void initialize();

		GalaxyCluster* getGalaxy(uint32 galaxyId);
		std::list<GalaxyCluster*> getGalaxyList();
		std::list<GalaxyServer*> getConnectionServerList();
		std::list<GalaxyServer*> getConnectionServerList(uint32 galaxyId);
		std::list<GalaxyCharacter*> getCharacterList(uint32 accountId);
		GalaxyServer* getConnectionServer(uint32 galaxyId);

	protected:
		std::list<GalaxyCluster*> m_galaxies;
		std::list<GalaxyServer*> m_connectionServers;
	};
}

#endif // OPENSWG_SOEPROTOCOL_GALAXYMANAGER