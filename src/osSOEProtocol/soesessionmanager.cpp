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
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/soesessionlistener.h>
#include <osSOEProtocol/soesessionmanager.h>
#include <osSOEProtocol/soelayermessages.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

SOESessionManager::SOESessionManager()
: SessionManager()
{}
    
void SOESessionManager::update(const uint64 updateTimestamp)
{
	SessionManager::update(updateTimestamp);
}

void SOESessionManager::initialize()
{
    // Perfect opportunity to register for a few default events.
    EventListenerPtr listener (GS_NEW SOESessionListener(this));
    safeAddListener(listener, EventType(Event_RemoteMessage::gkName));
    safeAddListener(listener, EventType(Event_SessionRequested::gkName));
    safeAddListener(listener, EventType(Event_DisconnectRequested::gkName));
}

boost::optional<SessionPtr> SOESessionManager::createSession(gsNetwork::NetworkMessagePtr message, gsNetwork::NetworkAddressPtr address, GameSocket *socket)
{
	SessionMap::iterator i = m_sessions.find(address->getAddressString());
	
	if (i != m_sessions.end())
	{
		Log::getMainLog().error("Session already exists for address [%s]", address->getAddressString().c_str());
		return NULL;
	}

	boost::shared_ptr<SessionRequestMessage> sessionRequest = boost::shared_dynamic_cast<SessionRequestMessage>(message);
	
	SOESessionPtr session(GS_NEW SOESession(address, socket));
	session->setCrcSeed(generateRandomCrcSeed());
	session->setConnectionId(sessionRequest->connectionId);
	session->setMaxPacketSize(sessionRequest->maxPacketSize);
	session->setValid(true);
	session->setOpcodeFactory(m_opcodeFactory);

	addSession(session);

	boost::shared_ptr<SessionResponseMessage> sessionResponse(GS_NEW SessionResponseMessage);
	sessionResponse->connectionId = session->getConnectionId();
	sessionResponse->crcSeed = session->getCrcSeed();
	sessionResponse->maxPacketSize = session->getMaxPacketSize();

	session->sendToRemote(sessionResponse);

	safeQueueEvent(EventPtr(GS_NEW Event_SessionCreated(session)));

	return session;
}

