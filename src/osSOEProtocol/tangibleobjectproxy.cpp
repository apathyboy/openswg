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

#include <osSOEProtocol/tangibleobject.h>
#include <osSOEProtocol/tangibleobjectproxy.h>
#include <osSOEProtocol/objectpropertytypes.h>
#include <osSOEProtocol/objlinkmessage.h>
#include <osSOEProtocol/tano3message.h>
#include <osSOEProtocol/tano6message.h>
#include <osSOEProtocol/tano8message.h>
#include <osSOEProtocol/tano9message.h>
#include <osSOEProtocol/creoinitmessage.h>
#include <osSOEProtocol/objclosemessage.h>
#include <osSOEProtocol/objpreclosemessage.h>
#include <gsServer/session.h>
#include <gsCore/log.h>
#include <gsCore/datastore.h>

using namespace gsCore;
using namespace gsServer;
using namespace osSOEProtocol;

TangibleObjectProxy::TangibleObjectProxy()
: ObjectProxy()
, m_linkType(ObjLinkMessage::WORLD_LINK)
{}

void TangibleObjectProxy::createTemplate()
{
	createObject();
}

void TangibleObjectProxy::createObject()
{
	boost::shared_ptr<TangibleObject> tanoObject(GS_NEW TangibleObject);
	m_object = tanoObject;

	buildPropertyMap();
}

void TangibleObjectProxy::buildPropertyMap()
{
	ObjectProxy::buildPropertyMap();

    const std::string GROUPNAME = "Tangible";

	boost::shared_ptr<TangibleObject> tangible = boost::shared_dynamic_cast<TangibleObject>(m_object);

	addProperty(new StringObjectProperty(
		"CustomName", "Custom Name", 
		makeFunctor((CBFunctor1<std::string>*)0, *tangible, &TangibleObject::setCustomName), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *tangible, &TangibleObject::getCustomName), 
		"Custom name of the tangible object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Color", "Color", 
		makeFunctor((CBFunctor1<std::string>*)0, *tangible, &TangibleObject::setColor), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *tangible, &TangibleObject::getColor), 
		"Custom color of the tangible object.", 
		GROUPNAME));
	
	addProperty(new BooleanObjectProperty(
		"Equipped", "Equipped", 
		makeFunctor((CBFunctor1<bool>*)0, *tangible, &TangibleObject::setEquipped), 
		makeFunctor((CBFunctor0wRet<bool>*)0, *tangible, &TangibleObject::getEquipped), 
		"Signals whether the item is equipped or not.", 
		GROUPNAME));
}

void TangibleObjectProxy::createFromTemplate(std::string templateItem)
{
	createObject();

	std::string::size_type pos = templateItem.find("/shared_");
	pos +=8;
	std::string::size_type endPos = templateItem.find_last_of(".");
	std::string type = templateItem.substr(pos, endPos - pos);

	getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(templateItem);
	getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue("wearables_name");
	getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(type);
}

void TangibleObjectProxy::store()
{
	try
    {
		
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT character_items.id "
		  << "FROM character_items "
		  << "WHERE object_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		
        mysqlpp::Result result = q.store();
                
		if (result)
        {
			mysqlpp::Row row = result.fetch_row();

		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "UPDATE `character_items` "
          << "SET character_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->getValue() << " , "
		  << " object_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()  << " , "
          << " custom_name = \"" << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("CustomName"))->getValue() << "\" , "
          << " color = \"" << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Color"))->getValue() << "\" , "
		  << " equipped = " << getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->getValue() << " , "
		  << " model = \"" << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue() << "\" , "
		  << " category = \"" << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue() << "\" , "
		  << " type = \"" << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue() << "\" , "
          << " quaternion_x = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->getValue() << " , "
          << " quaternion_y = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->getValue() << " , "
          << " quaternion_z = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->getValue() << " , "
          << " quaternion_w = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->getValue() << " , "
          << " position_x = " << getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue() << " , "
          << " position_y = " << getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue() << " , "
          << " position_z = " << getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue() << " , "
          << " scale = " << getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->getValue() << " , "
          << " state = " << getPropertyAs<UintObjectProperty*>(std::string("State"))->getValue() << "  "
          << "WHERE character_items.id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->getValue() << " LIMIT 1";
		
		mysqlpp::ResNSel result = q.execute();
          
		if (! result.success)
        {
			Log::getMainLog().error("Unable to update item");
			return;
        }
		}
	}
  
	catch (const mysqlpp::BadQuery& er)
    {
        // handle any query errors.
        Log::getMainLog().error("Query error: %s", er.what());
		return;
    }
	
	catch (const mysqlpp::EndOfResults&) {
		// Continue normally.
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

        q << "INSERT INTO `character_items` (`character_id`, `object_id`, `custom_name`, "
		  << "  `color`, `equipped`, `model`, `category`, `type`, "
          << "  `quaternion_x`, `quaternion_y`, `quaternion_z`, `quaternion_w`, "
          << "  `position_x`, `position_y`, `position_z`, "
          << "  `scale`, `created_on`, `state`) "
		  << "VALUES (" << getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->getValue() << ", "
          << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("CustomName"))->getValue() << ", " 
		  <<  mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Color"))->getValue() << ", "
          << getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->getValue() << ", "
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue() << ", "
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue() << ", " // Hardcoded object category
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue() << ", " // Hardcoded object type
          << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->getValue() << ", " // Qx
          << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->getValue() << ", " // Qy
          << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->getValue() << ", " // Qz
          << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->getValue() << ", " // Qw
          << getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue() << ", " // Px
          << getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue() << ", " // Py
          << getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue() << ", " // Pz
          << getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->getValue() << ", "
          << "NOW(), "
          << getPropertyAs<UintObjectProperty*>(std::string("State"))->getValue() << ")"; // Active subscriber state

		mysqlpp::ResNSel result = q.execute();

		if (! result.success)
        {
			Log::getMainLog().error("Unable to create new item entry");
			return;
        }
	}
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		Log::getMainLog().error("Error: %s", er.what());
		return;
	}
}

void TangibleObjectProxy::loadFromDatabaseId(uint64 databaseId)
{
	createObject();

	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT character_items.id, "
          << "       character_items.character_id, "
		  << "		 character_items.object_id, "
          << "       character_items.custom_name, "
          << "       character_items.color, "
		  << "		 character_items.equipped, "
		  << "		 character_items.model, "
		  << "		 character_items.category, "
		  << "		 character_items.type, "
          << "       character_items.quaternion_x, "
          << "       character_items.quaternion_y, "
          << "       character_items.quaternion_z, "
          << "       character_items.quaternion_w, "
          << "       character_items.position_x, "
          << "       character_items.position_y, "
          << "       character_items.position_z, "
          << "       character_items.scale, "
          << "       character_items.state "
          << "FROM character_items "
          << "WHERE character_items.id = " << databaseId << " LIMIT 1";

        mysqlpp::Result result = q.store();
                
		if (result)
        {
			mysqlpp::Row row = result.fetch_row();
			
			getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64)row["id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64)row["object_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64)row["character_id"]);
			getPropertyAs<StringObjectProperty*>(std::string("CustomName"))->setValue((std::string)row["custom_name"]);
			getPropertyAs<StringObjectProperty*>(std::string("Color"))->setValue((std::string)row["color"]);
			getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue((bool)row["equipped"]);
			getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)row["model"]);
			getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)row["category"]);
			getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)row["type"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)row["quaternion_x"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)row["quaternion_y"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)row["quaternion_z"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)row["quaternion_w"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)row["position_x"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)row["position_y"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)row["position_z"]);
			getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)row["scale"]);
			getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint)row["state"]);		
        }
        
		else
        {
            Log::getMainLog().error("Failed to load player item: 0x%08x", databaseId);
        }
    }
  
	catch (const mysqlpp::BadQuery& er)
    {
        // handle any query errors.
        Log::getMainLog().error("Query error: %s", er.what());
		return;
    }
	
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		Log::getMainLog().error("Error: %s", er.what());
		return;
	}
}


void TangibleObjectProxy::sendReliableUpdate(Session* session)
{
	boost::shared_ptr<CreoInitMessage> creoInit(GS_NEW CreoInitMessage());
	creoInit->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	creoInit->quaternionX = getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->getValue();
	creoInit->quaternionY = getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->getValue();
	creoInit->quaternionZ = getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->getValue();
	creoInit->quaternionW = getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->getValue();
	creoInit->positionX = getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue();
	creoInit->positionY = getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue();
	creoInit->positionZ = getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue();
	creoInit->sharedModel = getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue();
	session->sendToRemote(creoInit);

	// Send Obj Link
	boost::shared_ptr<ObjLinkMessage> objLink(GS_NEW ObjLinkMessage());
	objLink->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	objLink->parentId = getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->getValue();
	objLink->linkType = m_linkType;
	session->sendToRemote(objLink);

	// Send TANO 3
	boost::shared_ptr<Tano3Message> tano3(GS_NEW Tano3Message());
	tano3->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	tano3->category = getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue();
	tano3->type = getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue();
	session->sendToRemote(tano3);

	// Send TANO 6
	boost::shared_ptr<Tano6Message> tano6(GS_NEW Tano6Message());
	tano6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(tano6);

	// Send TANO 8
	boost::shared_ptr<Tano8Message> tano8(GS_NEW Tano8Message());
	tano8->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(tano8);

	// Send TANO 9
	boost::shared_ptr<Tano9Message> tano9(GS_NEW Tano9Message());
	tano9->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(tano9);

	boost::shared_ptr<ObjCloseMessage> objClose(GS_NEW ObjCloseMessage());
	objClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objClose);	
}

