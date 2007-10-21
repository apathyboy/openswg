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

#include <gsNetwork/events.h>
#include <gsServer/servereventlistener.h>
#include <gsServer/sessionevents.h>
#include <osSOEProtocol/soesession.h>
#include <osSOEProtocol/soelayermessages.h>
#include <osSOEProtocol/serverheadermessage.h>
#include <osLogin/loginservereventlistener.h>
#include <gsServer/serverevents.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

LoginServerEventListener::LoginServerEventListener(ServerApplication* server)
: ServerEventListener(server)
{}

LoginServerEventListener::~LoginServerEventListener()
{}
	
void LoginServerEventListener::registerEvents(EventListenerPtr listener)
{
	ServerEventListener::registerEvents(listener);

	safeAddListener(listener, EventType(Event_SessionCreated::gkName));
	safeAddListener(listener, EventType(Event_AccountAuthenticated::gkName));
}

bool LoginServerEventListener::handleEvent(const gsCore::Event &event)
{
    if (_stricmp(event.getType().getStr(), Event_SessionCreated::gkName) == 0)
    {
        EventData_SessionCreated * eventData = event.getDataPtr<EventData_SessionCreated>();	

		boost::shared_ptr<ServerHeaderMessage> message(GS_NEW ServerHeaderMessage());
		message->serverType = m_server->getServerType();
		message->serverId = m_server->getServerId();

		eventData->session->sendToRemote(message);
	}
    if (_stricmp(event.getType().getStr(), Event_AccountAuthenticated::gkName) == 0)
    {
	}

	return false;
}

