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
#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/eventmanager.h>
#include <gsCore/processmanager.h>

#include <signal.h>

#ifdef WIN32
#define SIGQUIT 3 // Windows doesn't specify this
#endif

using namespace gsCore;
using namespace gsApplication;

#ifdef WIN32
//#include <omp.h>
#endif

volatile bool Application::m_running = false;

Application::Application()
{}

ConfigFile Application::getConfig()
{
    return m_config;
}

void Application::run()
{    
    // Once the application has been setup toggle the running state.
    if (! isRunning())
		toggleRunning();

    uint64_t currentTime = 0;
    // Start the main server loop.
    do
    {
        // Perform the time advance check. For now this checks
        // the current timestamp in milliseconds, eventually this 
        // will be replaced with a call to the global virtual time
        // manager which will sync time events across processes.
        currentTime = gsCore::getTimeInMs();

        // Advance the application forward to the current time.
        tick(currentTime);
		
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }
    while (Application::isRunning());

	LOG(INFO) << "Received exit signal... shutting down now.";

	shutdown();
}

void Application::initialize(const std::string& configFilename)
{
    m_eventManager   = GS_NEW EventManager("Global Event Manager", true);
    m_processManager = GS_NEW ProcessManager;
	
	hookSignals();
}

void Application::shutdown()
{
	unhookSignals();
}

bool Application::isRunning()
{
    return Application::m_running;
}

void Application::toggleRunning()
{
	if (Application::m_running)
        Application::m_running = false;
    else
        Application::m_running = true;
}

void Application::tick(uint64_t updateTimestamp)
{
    uint64_t deltaTimestamp = (updateTimestamp - m_lastUpdateTimestamp);
    m_lastUpdateTimestamp = updateTimestamp;

	m_eventManager->tick(deltaTimestamp);
	m_processManager->tick(deltaTimestamp);
}
		
void Application::hookSignals()
{
	// Provide hooks for termination signals.
	signal(SIGINT, Application::onSignal);
    signal(SIGQUIT, Application::onSignal);
    signal(SIGTERM, Application::onSignal);
    signal(SIGABRT, Application::onSignal);
    #ifdef _WIN32
    signal(SIGBREAK, Application::onSignal);
    #endif
}
		
void Application::unhookSignals()
{
    signal(SIGINT, 0);
    signal(SIGQUIT, 0);
    signal(SIGTERM, 0);
    signal(SIGABRT, 0);
    #ifdef _WIN32
    signal(SIGBREAK, 0);
    #endif
}
		
void Application::onSignal(int s)
{
    switch (s)
    {
        case SIGINT:
        case SIGQUIT:
        case SIGTERM:
        case SIGABRT:
        #ifdef _WIN32
        case SIGBREAK:
        #endif
			Application::toggleRunning();
            break;
    }

    signal(s, onSignal);
}

