/**
 * radial_menu.h
 *
 * Copyright (C) 2006, 2007 OpenSWG Team <http://www.openswg.com>
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

#include "osSOEProtocol/radialmenu.h"

#include <algorithm>

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/datastore.h>

using namespace gsCore;
using namespace osSOEProtocol;

void osSOEProtocol::buildRadialMenuMap(RadialMenuMap & radialMap)
{
    radialMap.clear();

    try
    {
        mysqlpp::Query q = Datastore::getGalaxyDB().query();

        q << "SELECT * FROM radial_menu";

        mysqlpp::StoreQueryResult result = q.store();
        
        if (result)
        {
            std::for_each(begin(result), end(result), [&radialMap] (const mysqlpp::Row& row) 
            {  
                RadialOption option;
                option.id = (uint8_t)((uint8_t)row["id"]-1); // Correct the offset from the database which starts from 1 instead of 0.
                option.caption = (std::string)row["caption"];
                option.command = (std::string)row["command"];
                option.range = (float)row["range"];
                option.useRadialTarget = (row["use_radial_target"]) ? false : true;

                radialMap[option.id] = option;
            });
        }
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
	}
}

