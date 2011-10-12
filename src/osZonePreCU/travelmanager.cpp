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

#include "osZonePreCU/travelmanager.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>
#include <gsCore/datastore.h>
#include <osSOEProtocol/opcodes.h>
#include <osSOEProtocol/postureupdatemessage.h>
#include <osSOEProtocol/selfpostureupdatemessage.h>
#include <osSOEProtocol/shuttleanimationmessage.h>
#include <osSOEProtocol/animationmessage.h>
#include <osSOEProtocol/tangibleobjectproxy.h>
#include <osSOEProtocol/creatureobjectproxy.h>
#include <osSOEProtocol/objectpropertytypes.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;


TravelManager::TravelManager(ObjectGrid* objectGrid)
: Process(PROC_TRAVEL)
, m_objectGrid(objectGrid)
{
	m_transportsLanded = true;
}

void TravelManager::updateTransports()
{
	if (! m_transportsLanded)
	{
		printf("Landing transports\n");
		m_transportsLanded = true;

		for (std::list<CreatureObjectProxyPtr>::iterator itor = m_transports.begin();
			itor != m_transports.end(); ++itor)
		{
			uint64_t objectId = (*itor)->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
			uint8_t posture = 0;
			(*itor)->getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->setValue(posture);
			
			boost::shared_ptr<ShuttleAnimationMessage> takeoff(GS_NEW ShuttleAnimationMessage);
			takeoff->objectId = objectId;
			takeoff->posture = posture;
			m_objectGrid->sendInRange(objectId,	takeoff);
			/*
			boost::shared_ptr<AnimationMessage> animation(GS_NEW AnimationMessage);
			animation->objectId = objectId;
			animation->animationCrc = 0xab290245;
			animation->posture = posture;
			m_objectGrid->sendInRange(objectId,	animation);

			boost::shared_ptr<SelfPostureUpdateMessage> selfPostureUpdate(GS_NEW SelfPostureUpdateMessage);
			selfPostureUpdate->objectId = objectId;
			selfPostureUpdate->posture = posture;
			m_objectGrid->sendInRange(objectId,	selfPostureUpdate);
			*/
		}
	}
	else
	{
		printf("Transports taking off\n");
		m_transportsLanded = false;
		// Send transport takeoff
		
		for (std::list<CreatureObjectProxyPtr>::iterator itor = m_transports.begin();
			itor != m_transports.end(); ++itor)
		{
			uint64_t objectId = (*itor)->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
			uint8_t posture = 2;
			(*itor)->getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->setValue(posture);
			
			boost::shared_ptr<ShuttleAnimationMessage> takeoff(GS_NEW ShuttleAnimationMessage);
			takeoff->objectId = objectId;
			takeoff->posture = posture;
			m_objectGrid->sendInRange(objectId,	takeoff);
			/*
			boost::shared_ptr<PostureUpdateMessage> postureUpdate(GS_NEW PostureUpdateMessage);
			postureUpdate->objectId = objectId;
			postureUpdate->posture = posture;
			m_objectGrid->sendInRange(objectId,	postureUpdate);

			boost::shared_ptr<AnimationMessage> animation(GS_NEW AnimationMessage);
			animation->objectId = objectId;
			animation->animationCrc = 0xab290245;
			animation->posture = posture;
			m_objectGrid->sendInRange(objectId,	animation);

			boost::shared_ptr<SelfPostureUpdateMessage> selfPostureUpdate(GS_NEW SelfPostureUpdateMessage);
			selfPostureUpdate->objectId = objectId;
			selfPostureUpdate->posture = posture;
			m_objectGrid->sendInRange(objectId,	selfPostureUpdate);
			*/
		}
	}
}

void TravelManager::update(const uint64_t updateTimestamp)
{
	if (updateTimestamp - m_lastCleanupTime > 500 * 60)
	{
		m_lastCleanupTime = updateTimestamp;
		updateTransports();
	}
}
        
void TravelManager::initialize()
{
	loadTicketVendors();
	loadTicketCollectors();
	loadTransports();
	// Load travel map
}

void TravelManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
}

void TravelManager::loadTransports()
{
			uint32_t count = 0;
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT transports.id, "
          << "       transports.zone_id, "
		  << "		 transports.object_id, "
		  << "		 transports.planet_id, "
		  << "	     transports.cell_id, "
		  << "		 transports.model, "
		  << "		 transports.category, "
		  << "		 transports.type, "
          << "       transports.quaternion_x, "
          << "       transports.quaternion_y, "
          << "       transports.quaternion_z, "
          << "       transports.quaternion_w, "
          << "       transports.position_x, "
          << "       transports.position_y, "
          << "       transports.position_z, "
          << "       transports.scale, "
          << "       transports.state "
          << "FROM transports ";
          //<< "WHERE character_items.id = " << databaseId << " LIMIT 1";
        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this, &count] (const mysqlpp::Row& row) 
            {  	
				boost::shared_ptr<CreatureObjectProxy> transport(GS_NEW CreatureObjectProxy);
				transport->createTemplate();
				transport->getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64_t)row["id"]);
				transport->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64_t)row["object_id"]);
				transport->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64_t)row["cell_id"]);
				transport->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)row["model"]);
				transport->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)row["category"]);
				transport->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)row["type"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)row["quaternion_x"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)row["quaternion_y"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)row["quaternion_z"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)row["quaternion_w"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)row["position_x"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)row["position_y"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)row["position_z"]);
				transport->getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)row["scale"]);
				transport->getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint32_t)row["state"]);
				++count;
				m_objectGrid->insert(transport);
				m_transports.push_back(transport);
			});
        }
        
		else
        {
            LOG(ERROR) << "Failed to load transports";
        }
    }
	catch (const mysqlpp::Exception& er)
    {
        LOG(ERROR) << "ERROR: " << er.what();
		return;
	}

    LOG(INFO) << "Transports loaded: " << count;
}

void TravelManager::loadTicketCollectors()
{
			uint32_t count = 0;
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT ticket_collectors.id, "
          << "       ticket_collectors.zone_id, "
		  << "		 ticket_collectors.object_id, "
		  << "		 ticket_collectors.planet_id, "
		  << "	     ticket_collectors.cell_id, "
		  << "		 ticket_collectors.model, "
		  << "		 ticket_collectors.category, "
		  << "		 ticket_collectors.type, "
          << "       ticket_collectors.quaternion_x, "
          << "       ticket_collectors.quaternion_y, "
          << "       ticket_collectors.quaternion_z, "
          << "       ticket_collectors.quaternion_w, "
          << "       ticket_collectors.position_x, "
          << "       ticket_collectors.position_y, "
          << "       ticket_collectors.position_z, "
          << "       ticket_collectors.scale, "
          << "       ticket_collectors.state "
          << "FROM ticket_collectors ";

        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this, &count] (const mysqlpp::Row& row) 
            {  	
				boost::shared_ptr<TangibleObjectProxy> collector(GS_NEW TangibleObjectProxy);
				collector->createTemplate();
				collector->getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64_t)row["id"]);
				collector->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64_t)row["object_id"]);
				collector->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64_t)row["cell_id"]);
				collector->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)row["model"]);
				collector->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)row["category"]);
				collector->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)row["type"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)row["quaternion_x"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)row["quaternion_y"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)row["quaternion_z"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)row["quaternion_w"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)row["position_x"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)row["position_y"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)row["position_z"]);
				collector->getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)row["scale"]);
				collector->getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint32_t)row["state"]);
				++count;
				m_objectGrid->insert(collector);
				m_ticketCollectors.push_back(collector);
			});
        }
        
		else
        {
            LOG(ERROR) << "Failed to load ticket collectors";
        }
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
            LOG(ERROR) << "ERROR: " << er.what();
		return;
	}
        
    LOG(INFO) << "Ticket collectors loaded: " << count;
}

void TravelManager::loadTicketVendors()
{
			uint32_t count = 0;
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT ticket_vendors.id, "
          << "       ticket_vendors.zone_id, "
		  << "		 ticket_vendors.object_id, "
		  << "		 ticket_vendors.planet_id, "
		  << "	     ticket_vendors.cell_id, "
		  << "		 ticket_vendors.model, "
		  << "		 ticket_vendors.category, "
		  << "		 ticket_vendors.type, "
          << "       ticket_vendors.quaternion_x, "
          << "       ticket_vendors.quaternion_y, "
          << "       ticket_vendors.quaternion_z, "
          << "       ticket_vendors.quaternion_w, "
          << "       ticket_vendors.position_x, "
          << "       ticket_vendors.position_y, "
          << "       ticket_vendors.position_z, "
          << "       ticket_vendors.scale, "
          << "       ticket_vendors.state "
          << "FROM ticket_vendors ";
          //<< "WHERE character_items.id = " << databaseId << " LIMIT 1";
        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this, &count] (const mysqlpp::Row& row) 
            { 
				boost::shared_ptr<TangibleObjectProxy> vendor(GS_NEW TangibleObjectProxy);
				vendor->createTemplate();
				vendor->getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64_t)row["id"]);
				vendor->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64_t)row["object_id"]);
				vendor->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64_t)row["cell_id"]);
				vendor->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)row["model"]);
				vendor->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)row["category"]);
				vendor->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)row["type"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)row["quaternion_x"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)row["quaternion_y"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)row["quaternion_z"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)row["quaternion_w"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)row["position_x"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)row["position_y"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)row["position_z"]);
				vendor->getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)row["scale"]);
				vendor->getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint32_t)row["state"]);
				++count;
				m_objectGrid->insert(vendor);
				m_ticketVendors.push_back(vendor);
			});
        }
        
		else
        {
            LOG(ERROR) << "Failed to load ticket vendors";
        }
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
	}
        
    LOG(INFO) << "Ticket vendors loaded: " << count;
}

void TravelManager::loadTravelMap()
{}

