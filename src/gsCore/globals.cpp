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

#include <gsCore/globals.h>

/**
 * A simple method that returns the requested system environment 
 * varaible. If the env var is not set, the local path will be returned.
 *
 * @param env System environment variable to lookup and return
 * @return Value of the requested system environment variable.
 */
GS_CORE_EXPORT std::string gsCore::GetEnvironment( const std::string& env )
{
    if ( char* ptr = getenv( env.c_str() ) )
    {
        return std::string(ptr);
    }
    else
    {
        return std::string("./");
    }
}


/**
 * If the GALAXY_ROOT environment is not set, the local direcotry will
 * be returned.
 */
GS_CORE_EXPORT std::string gsCore::GetGalaxyRootPath()
{
    return GetEnvironment("GALAXY_ROOT");
}

