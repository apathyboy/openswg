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

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

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
    LOG(INFO) << "Event snoop : event " << std::hex << event.getType().getIdent()
        << " [" << event.getType().getStr() << "] "
        << " time " << event.getTime();

	return false;
}



