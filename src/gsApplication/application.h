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

#ifndef GALAXY_APPLICATION_APPLICATION
#define GALAXY_APPLICATION_APPLICATION

#include <cstdint>

#include <gsCore/config.h>
#include <gsCore/macros.h>

#include <string>

namespace gsCore
{
    class EventManager;
    class ProcessManager;
}

namespace gsApplication
{
    class Application
    {
    public:
        Application();
		virtual ~Application() {}
        
        virtual void initialize(const std::string& configFilename);
		virtual void shutdown();

        static bool isRunning();
        static void toggleRunning();

        ConfigFile getConfig();
        virtual void run();

        virtual void tick(uint64_t updateTimestamp);

        static volatile bool m_running;

		void hookSignals();
		void unhookSignals();
		static void onSignal(int s);

    protected:

        uint64_t m_lastUpdateTimestamp;

        gsCore::EventManager* m_eventManager;
        gsCore::ProcessManager* m_processManager;

        ConfigFile m_config;
    };
}

#endif // GALAXY_APPLICATION_APPLICATION

