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
#include <gsCore/eventlistener.h>
#include <gsCore/eventmanager.h>

using namespace gsCore;

//--

EventSnooper::EventSnooper()
{
}

EventSnooper::~EventSnooper()
{
}

void EventSnooper::registerEvents(EventListenerPtr listener)
{
    safeAddListener(listener, EventType(gsCore::kpWildcardEventType));
}

bool EventSnooper::handleEvent( Event const & event )
{

#ifdef _VS2005_
    Log::getEventLog().info(
		"Event Snoop : event %08lx time %g : type %08lx [%s] : packet \n%s",
		& event,
		event.getTime(),
		event.getType().getIdent(),
		event.getType().getStr());
#else
	Log::getEventLog().info(
		"Event Snoop : event %08lx time %g : type %08lx [%s] : ",
		& event,
		event.getTime(),
		event.getType().getIdent(),
		event.getType().getStr());
#endif

	return false;
}



