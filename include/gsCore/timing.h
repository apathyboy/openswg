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

#ifndef GALAXY_CORE_TIMING
#define GALAXY_CORE_TIMING

#include <gsCore/globals.h>
#include <gsCore/types.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <mmsystem.h>
# include <time.h>
#else
# if defined(__FreeBSD__) || defined(__APPLE_CC__)
#   include <time.h>
# endif
#   include <sys/timeb.h>
#endif

namespace gsCore
{
	
	static inline uint64 generateObjectId()
	{
		static uint64 idTimestamp = time(NULL);
		static uint64 idChunk = 0;

		uint64 currentTime = time(NULL);

		if (idTimestamp == currentTime)
		{
			++idChunk;
		}
		else 
		{
			idChunk = 1;
			idTimestamp = currentTime;
		}

		return (uint64)(idTimestamp+(idChunk*100));
	}

    inline uint64 GS_CORE_EXPORT getTime()
    {
        return (uint64)time(NULL);
    }

	inline uint64 GS_CORE_EXPORT getTimeInMs()
	{
		uint32 time_in_ms = 0;
    #if _WIN32
		time_in_ms = timeGetTime();
    #else
		struct timeb tp;
		ftime(&tp);

		time_in_ms = tp.time * 1000 + tp.millitm;
    #endif

		return (uint64)time_in_ms;
	}
}

#endif // GALAXY_CORE_TIMING