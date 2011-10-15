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

#include <crtdbg.h>

#include <memory>
#include <string>

#include <glog/logging.h>

#include "osLogin/loginserver.h"

using namespace std;

// Global constants.
const string kpAppName = "OpenSWG Login Server";
const string kpVersion = "1.0.0";
const string kpConfigFile = "config/login.ini";

int main(int argc, char *argv[])
{    
	// Set up checks for memory leaks.
	// Game Coding Complete reference - Chapter 12, page 446
	//
//	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// set this flag to keep memory blocks around
//	tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;				// this flag will cause intermittent pauses in your game!

	// perform memory check for each alloc/dealloc
//	tmpDbgFlag |= _CRTDBG_CHECK_ALWAYS_DF;				// remember this is VERY VERY SLOW!

	// always perform a leak check just before app exits.
//	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;					

//	_CrtSetDbgFlag(tmpDbgFlag);
    
    // Initialize the google logging.
    google::InitGoogleLogging(argv[0]);

    #ifndef _WIN32
        google::InstallFailureSignalHandler();
    #endif

    FLAGS_log_dir = "./logs";
    FLAGS_stderrthreshold = 1;

    // Print out headers for the console.
    cout << kpAppName << " v" << kpVersion << "\n";
    cout << "Copyright (c) 2006 - 2011 the OpenSWG Team\n\n" << endl;
    
    // Create an instance of the server application. We'll customize
    // this by adding in our own custom sockets and processes.
	LoginServer app("LoginServer:29511", 29511);

    // This is where the configuration file is parsed and we
    // can begin setting up the application environment.
    app.initialize(kpConfigFile);
    
    // Start the main server loop.
    app.run();

	//_CRTDBG_LEAK_CHECK_DF is used at program initialization to force a 
	//   leak check just before program exit. This is important because
	//   some classes may dynamically allocate memory in globally constructed
	//   objects.
	//
//	_CrtDumpMemoryLeaks();					// Reports leaks to stderr

    return 0;
}