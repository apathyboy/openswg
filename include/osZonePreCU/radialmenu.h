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

#ifndef OPENSWG_ZONEPRECU_RADIALMENU
#define OPENSWG_ZONEPRECU_RADIALMENU

#include <gsCore/types.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>
#include <zthread/Singleton.h>

namespace osZonePreCU
{
    class RadialOption;
    typedef std::map<uint8, RadialOption> RadialMenuMap;

    #define sRadialMenuMap ZThread::Singleton<RadialMenuMap>::instance()

    class RadialOption
    {
    public:
        uint8 id;
        std::string caption;
        float range;
        std::string command;
        bool useRadialTarget;
    };

    void buildRadialMenuMap(RadialMenuMap & radialMap);
}

#endif // OPENSWG_ZONEPRECU_RADIALMENU