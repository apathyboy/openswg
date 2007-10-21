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

#ifndef GALAXY_CORE_LOGEVENTS
#define GALAXY_CORE_LOGEVENTS

#include <gsCore/event.h>
#include <gsCore/eventlistener.h>
#include <gsCore/export.h>

namespace gsCore
{	
    class GS_CORE_EXPORT PacketLogListener : public IEventListener
    {
    public:
        PacketLogListener();
        virtual ~PacketLogListener();
        char const * getName(void) { return "PacketLogListener"; }
        bool handleEvent(Event const & event);
    };
}

#endif // GALAXY_CORE_LOGEVENTS

