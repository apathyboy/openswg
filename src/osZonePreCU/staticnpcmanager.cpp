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

#include "osZonePreCU/staticnpcmanager.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>
#include <gsCore/datastore.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/tangibleobjectproxy.h>
#include <osSOEProtocol/creatureobjectproxy.h>
#include <osSOEProtocol/objectpropertytypes.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;


StaticNpcManager::StaticNpcManager(ObjectGrid* objectGrid)
: Process(PROC_TRAVEL)
, m_objectGrid(objectGrid)
{
}

void StaticNpcManager::update(const uint64_t updateTimestamp)
{
}
        
void StaticNpcManager::initialize()
{
	loadStaticNpcs();
	// Load travel map
}

void StaticNpcManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
}

void StaticNpcManager::loadStaticNpcs()
{
			uint32_t count = 0;
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT static_npcs.id, "
        << "       static_npcs.zone_id, "
		  << "		 static_npcs.object_id, "
		  << "		 static_npcs.planet_id, "
		  << "	     static_npcs.cell_id, "
		  << "		 static_npcs.model, "
		  << "		 static_npcs.category, "
		  << "		 static_npcs.type, "
        << "       static_npcs.quaternion_x, "
        << "       static_npcs.quaternion_y, "
        << "       static_npcs.quaternion_z, "
        << "       static_npcs.quaternion_w, "
        << "       static_npcs.position_x, "
        << "       static_npcs.position_y, "
        << "       static_npcs.position_z, "
        << "       static_npcs.scale, "
        << "       static_npcs.state "
        << "FROM static_npcs ";

        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this, &count] (const mysqlpp::Row& row) 
            {  	
				boost::shared_ptr<CreatureObjectProxy> staticNpc(GS_NEW CreatureObjectProxy);
				staticNpc->createTemplate();
				staticNpc->getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64_t)row["id"]);
				staticNpc->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64_t)row["object_id"]);
				staticNpc->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64_t)row["cell_id"]);
				staticNpc->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)row["model"]);
				staticNpc->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)row["category"]);
				staticNpc->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)row["type"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)row["quaternion_x"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)row["quaternion_y"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)row["quaternion_z"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)row["quaternion_w"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)row["position_x"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)row["position_y"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)row["position_z"]);
				staticNpc->getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)row["scale"]);
				staticNpc->getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint32_t)row["state"]);
				++count;
				m_objectGrid->insert(staticNpc);
				m_staticNpcs.push_back(staticNpc);
			});
        }
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
		return;
	}

    LOG(INFO) << "Static NPCs loaded: " << count;
}

