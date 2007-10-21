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

#ifndef GALAXY_NETWORK_GAMESOCKETLISTNER
#define GALAXY_NETWORK_GAMESOCKETLISTNER

#include <gsCore/eventmanager.h>

#include <gsNetwork/export.h>

#include <Sockets/SocketHandler.h>

#include <zthread/Runnable.h>

namespace gsNetwork
{
    class GS_NETWORK_EXPORT GameSocketListener : public SocketHandler, 
												 public gsCore::IEventListener,
                                                 public ZThread::Runnable
    {
    public:
        GameSocketListener();

	public:
        char const * getName(void) { return "GameSocketListener"; }
        bool handleEvent(gsCore::Event const & event);

		static void registerEvents(gsCore::EventListenerPtr listener);

    public:
        virtual void run();

        bool isRunning();
        void toggleRunning();

    protected:
        bool m_isRunning;
    };
}

#endif // GALAXY_NETWORK_GAMESOCKETLISTNER
