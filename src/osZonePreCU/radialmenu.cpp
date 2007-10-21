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

#include <osZonePreCU/radialmenu.h>
#include <gsCore/log.h>
#include <gsCore/datastore.h>

using namespace gsCore;
using namespace osZonePreCU;

void osZonePreCU::buildRadialMenuMap(RadialMenuMap & radialMap)
{
    radialMap.clear();

    try
    {
        mysqlpp::Query q = Datastore::getGalaxyDB().query();

        q << "SELECT * FROM radial_menu";

        mysqlpp::Result result = q.store();
        
        if (result)
        {
            mysqlpp::Row row;
            while (row = result.fetch_row())
            {
                RadialOption option;
                option.id = (uint8)((uint8)row["id"]-1); // Correct the offset from the database which starts from 1 instead of 0.
                option.caption = (std::string)row["caption"];
                option.command = (std::string)row["command"];
                option.range = (float)row["range"];
                option.useRadialTarget = (row["use_radial_target"]) ? false : true;

                radialMap[option.id] = option;
            }
        }

        else
        {
            Log::getMainLog().error("Failed to load radial menu options: %s", q.error().c_str());
        }
    }
    catch (const mysqlpp::BadQuery& er)
    {
        // handle any query errors.
        Log::getMainLog().error("Query error: %s", er.what());
    }
	catch (const mysqlpp::EndOfResults&) {
		// Continue normally.
        Log::getMainLog().info("%i Radial Menu Options Loaded", radialMap.size());
	}
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		Log::getMainLog().error("%s", er.what());
	}
}

