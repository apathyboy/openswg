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

#include <gsCore/eventlistener.h>
#include <gsNetwork/events.h>
#include <gsServer/sessionevents.h>
#include <osSOEProtocol/soeclientsocket.h>
#include <osSOEProtocol/soesocketfactory.h>
#include <osSOEProtocol/soesocketeventlistener.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

SOESocketFactory::SOESocketFactory(SessionManager* sessionManager)
: m_sessionManager(sessionManager)
{}

std::shared_ptr<UdpEventSocket> SOESocketFactory::createClientSocket(boost::asio::io_service &io_service, uint16_t port)
{
    auto socket = std::make_shared<SOEClientSocket>(m_sessionManager, io_service, port);
		
	EventListenerPtr listener(GS_NEW SOESocketEventListener(socket));
    safeAddListener(listener, EventType(Event_SessionCreated::gkName));

    return socket;
}

