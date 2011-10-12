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

#include <gsApplication/application.h>

#include <boost/thread/thread.hpp>

#include <gsNetwork/events.h>
#include <gsNetwork/gamesocketlistener.h>

using namespace gsCore;
using namespace gsNetwork;

GameSocketListener::GameSocketListener()
: SocketHandler()
{
    m_isRunning = false;
}

void GameSocketListener::registerEvents(gsCore::EventListenerPtr listener)
{
	safeAddListener(listener, EventType(gsNetwork::Event_RemoteMessage::gkName));
}

bool GameSocketListener::handleEvent(const gsCore::Event &event)
{
    if (_stricmp(event.getType().getStr(), Event_RemoteMessage::gkName) == 0)
    {
		printf("Game Socket Event Triggered!\n");
	}

	return false;
}

void GameSocketListener::toggleRunning()
{
    m_isRunning = !m_isRunning;
}

bool GameSocketListener::isRunning()
{
    return m_isRunning;
}

void GameSocketListener::run()
{
	while (isRunning() && GetCount())
    {
        Select(1, 0);
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
}

