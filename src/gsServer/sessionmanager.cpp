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
// ************************

#include "gsServer/sessionmanager.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/event.h>
#include <gsNetwork/events.h>
#include <gsServer/sessioneventlistener.h>
#include <gsServer/sessionmanager.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;

SessionManager::SessionManager()
: m_lastCleanupTime(0)
, Process(PROC_MANAGESESSIONS, 0)
{}
    
void SessionManager::update(const uint64_t updateTimestamp)
{
	Process::update(updateTimestamp);

	if (updateTimestamp - m_lastCleanupTime > 1000 * 60)
	{
		m_lastCleanupTime = updateTimestamp;
		removeDeadSessions(updateTimestamp);
	}

	for (SessionMap::iterator i = m_sessions.begin();
		i != m_sessions.end();)
	{
		SessionPtr session = (*i).second;

		if (session->isValid())
		{
			session->update();
			++i;
		}
		else
		{
            LOG(WARNING) << "Removing invalid session for address: " << (*i).second->getRemoteAddress()->getAddressString();
			removeSession(i++);
		}
	}
}

void SessionManager::removeDeadSessions(const uint64_t updateTimestamp)
{
	SessionMap::iterator i = m_sessions.begin();
	while (i != m_sessions.end())
	{
		if (updateTimestamp - (*i).second->getLastUpdateTime() > 1000 * 60)
		{
            LOG(WARNING) << "Removing inactive session for address: " << (*i).second->getRemoteAddress()->getAddressString();
			removeSession(i++);
		}
		else 
			i++;
	}
}

boost::optional<SessionPtr> SessionManager::createSession(gsNetwork::NetworkMessagePtr message, gsNetwork::NetworkAddressPtr address, GameSocket *socket)
{
	return NULL;
}
		
void SessionManager::queueRemoteMessage(gsNetwork::BinaryPacketPtr packet, gsNetwork::NetworkAddressPtr address)
{
}

void SessionManager::initialize()
{
}

void SessionManager::addSession(SessionPtr session)
{
	SessionMap::iterator i = m_sessions.find(session->getRemoteAddress()->getAddressString());

	if (i != m_sessions.end())
		return;

	m_sessions[session->getRemoteAddress()->getAddressString()] = session;
    
    LOG(INFO) << "Current session count: " << m_sessions.size();
}

void SessionManager::removeSession(SessionMap::iterator i)
{
    SessionPtr session = (*i).second;
    i = m_sessions.erase(i);
            
    LOG(INFO) << "Current session count: " << m_sessions.size();
}

void SessionManager::removeSession(SessionPtr session)
{
	for (SessionMap::iterator i = m_sessions.begin(); i != m_sessions.end();++i)
	{
		if (session == (*i).second)
		{
			removeSession(i);
			return;
		}
	}
}

boost::optional<SessionPtr> SessionManager::findSession(std::string address)
{
    boost::optional<SessionPtr> session;
	SessionMap::iterator i = m_sessions.find(address);

	if (i != m_sessions.end())
		session = (*i).second;

    return session;
}

