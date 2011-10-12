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

#include <cstdint>

#include <boost/date_time.hpp>

namespace gsCore
{
	
	static inline uint64_t generateObjectId()
	{
		static uint64_t idTimestamp = time(NULL);
		static uint64_t idChunk = 0;

		uint64_t currentTime = time(NULL);

		if (idTimestamp == currentTime)
		{
			++idChunk;
		}
		else 
		{
			idChunk = 1;
			idTimestamp = currentTime;
		}

		return (uint64_t)(idTimestamp+(idChunk*100));
	}

    inline uint64_t getTime()
    {
        static boost::posix_time::ptime time_since_epoch(boost::gregorian::date(1970,1,1));

        auto now = boost::posix_time::microsec_clock::local_time();

        auto diff = now - time_since_epoch;

        return diff.total_seconds();
    }

	inline uint64_t getTimeInMs()
	{
        static boost::posix_time::ptime time_since_epoch(boost::gregorian::date(1970,1,1));

        auto now = boost::posix_time::microsec_clock::local_time();

        auto diff = now - time_since_epoch;

        return diff.total_milliseconds();
	}
}

#endif // GALAXY_CORE_TIMING