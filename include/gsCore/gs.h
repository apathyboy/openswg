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

#ifndef GALAXY_GS
#define GALAXY_GS

#include <gsCore/globals.h>
#include <gsCore/macros.h>
#include <gsCore/timing.h>
#include <gsCore/types.h>

// Event System
#include <gsCore/event.h>
#include <gsCore/eventdata.h>
#include <gsCore/eventlistener.h>
#include <gsCore/eventmanager.h>
#include <gsCore/eventtype.h>

/** 
 * @namespace gsCore
 *
 * The gsCore namespace contains basic, low-level functionality which is mostly
 * required for all GSF based applications.
 */
namespace gsCore
{
}

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)

    // Automatic library inclusion macros that use the #pragma/lib feature
    #undef GS_H_WINMM_LIB
    #undef GS_H_GSCORE_LIB

    // Setup debug vs. release library names
    #if defined(_DEBUG)
        #ifndef GS_CORE_LIBRARY  
            #define  GS_H_GSCORE_LIB "gsCored.lib"
        #endif
    #else
        #ifndef GS_CORE_LIBRARY
            #define GS_H_GSCORE_LIB "gsCore.lib"
        #endif
    #endif

    #define GS_H_WINMM_LIB  "winmm.lib"

    // You may turn off this include message by defining _NOAUTOLIB 
    #ifndef _NOAUTOLIBMSG
        #pragma message( "Will automatically link with " GS_H_WINMM_LIB )
        #ifndef GS_CORE_LIBRARY
            #pragma message( "Will automatically link with " GS_H_GSCORE_LIB )
        #endif
    #endif

    // Actually do the linking
    #pragma comment(lib, GS_H_WINMM_LIB)
    #ifndef GS_CORE_LIBRARY
        #pragma comment(lib, GS_H_GSCORE_LIB)
    #endif

#endif

#endif // GALAXY_GS