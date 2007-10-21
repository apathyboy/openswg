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
#include <gsNetwork/events.h>
#include <gsServer/sessionevents.h>
#include <gsServer/serverevents.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/galaxylistmessage.h>
#include <osSOEProtocol/connectionserverlistmessage.h>
#include <osSOEProtocol/characterlistmessage.h>
#include <osSOEProtocol/galaxymanagerlistener.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

GalaxyManagerListener::GalaxyManagerListener(GalaxyManager* galaxyManager)
: m_galaxyManager(galaxyManager)
{}

GalaxyManagerListener::~GalaxyManagerListener()
{}

bool GalaxyManagerListener::handleEvent(Event const & event)
{
    if (_stricmp(event.getType().getStr(), Event_AccountAuthenticated::gkName) == 0)
    {		
		EventData_AccountAuthenticated * eventData = event.getDataPtr<EventData_AccountAuthenticated>();

		boost::shared_ptr<GalaxyListMessage> galaxyList(GS_NEW GalaxyListMessage);
		galaxyList->galaxies = m_galaxyManager->getGalaxyList();

		eventData->session->sendToRemote(galaxyList);

		boost::shared_ptr<ConnectionServerListMessage> connectionServerList(GS_NEW ConnectionServerListMessage);
		connectionServerList->connectionServers = m_galaxyManager->getConnectionServerList();

		eventData->session->sendToRemote(connectionServerList);

		boost::shared_ptr<CharacterListMessage> characterList(GS_NEW CharacterListMessage);
		characterList->characters = m_galaxyManager->getCharacterList(eventData->session->getAccountId());

		eventData->session->sendToRemote(characterList);
	}

	return false;
}

