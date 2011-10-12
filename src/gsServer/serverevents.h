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

#ifndef GALAXY_SERVER_SERVEREVENTS
#define GALAXY_SERVER_SERVEREVENTS

#include <gsCore/eventmanager.h>
#include <gsCore/globals.h>
#include <gsCore/macros.h>
#include <gsServer/session.h>

namespace gsServer
{
    /**
     * 
     */
    struct EventData_AccountAuthenticated : public gsCore::IEventData
    {
		explicit EventData_AccountAuthenticated(Session* inSession)
            : session(inSession)
        {}

		Session* session;
    };

    class Event_AccountAuthenticated : public gsCore::Event
    {
    public:
        static char const * const gkName;
        explicit Event_AccountAuthenticated(Session* session)
            : gsCore::Event(gkName,
                    0,
                    gsCore::IEventDataPtr(GS_NEW EventData_AccountAuthenticated(session)))
        {}        
    };
}

#endif // GALAXY_SERVER_SERVEREVENTS

