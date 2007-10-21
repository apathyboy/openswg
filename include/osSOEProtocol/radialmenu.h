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

#ifndef OPENSWG_SOEPROTOCOL_RADIALMENU
#define OPENSWG_SOEPROTOCOL_RADIALMENU

#include <gsCore/types.h>
#include <osSOEProtocol/export.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>
#include <zthread/Singleton.h>

namespace osSOEProtocol
{
    class RadialOption;
    typedef OS_SOEPROTOCOL_EXPORT std::map<uint8, RadialOption> RadialMenuMap;

    #define sRadialMenuMap ZThread::Singleton<RadialMenuMap>::instance()

    class OS_SOEPROTOCOL_EXPORT RadialOption
    {
    public:
        uint8 id;
		uint8 index;
		uint8 parentIndex;
        std::string caption;
        float range;
        std::string command;
        bool useRadialTarget;
    };

    void OS_SOEPROTOCOL_EXPORT buildRadialMenuMap(RadialMenuMap & radialMap);
}

#endif // OPENSWG_SOEPROTOCOL_RADIALMENU