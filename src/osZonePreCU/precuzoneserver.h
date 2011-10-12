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

#ifndef OPENSWG_ZONEPRECU_PRECUZONESERVER
#define OPENSWG_ZONEPRECU_PRECUZONESERVER

#include <gsCore/types.h>
#include <gsServer/opcodehandler.h>
#include <gsServer/serverapplication.h>
#include <gsServer/session.h>
#include <gsNetwork/binarypacket.h>
#include <osSOEProtocol/galaxymanager.h>
#include <osSOEProtocol/soesessionmanager.h>

#include <osZonePreCU/travelmanager.h>
#include <osZonePreCU/staticnpcmanager.h>
#include <osZonePreCU/authmanager.h>
#include <osZonePreCU/charactercreationmanager.h>
#include <osSOEProtocol/objectmanager.h>

#include <string>

namespace osZonePreCU
{
	class PreCUZoneServer : public gsServer::ServerApplication
	{
    public:
        PreCUZoneServer(std::string serverType, uint32 serverId);
        virtual ~PreCUZoneServer();

		virtual void initialize(const std::string& configFilename);

	protected:
		AuthManager* m_authManager;
		CharacterCreationManager* m_charCreationManager;
		osSOEProtocol::ObjectManager* m_objectManager;
		TravelManager* m_travelManager;
		StaticNpcManager* m_staticNpcManager;
		osSOEProtocol::ObjectGrid* m_objectGrid;
		gsServer::SessionManager* m_sessionManager;
		osSOEProtocol::GalaxyManager* m_galaxyManager;
	};
}

#endif // OPENSWG_ZONEPRECU_PRECUZONESERVER

