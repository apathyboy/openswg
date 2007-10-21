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

#include <gsCore/macros.h>
#include <gsCore/log.h>
#include <gsServer/session.h>
#include <gsCore/datastore.h>
#include <osZonePreCU/objectpropertytypes.h>
#include <osZonePreCU/playercreatureobject.h>
#include <osZonePreCU/playercreatureobjectproxy.h>

#include <osSOEProtocol/settingunk1message.h>
#include <osSOEProtocol/unkint900message.h>
#include <osSOEProtocol/loadterrainmessage.h>
#include <osSOEProtocol/timeupdatemessage.h>
#include <osSOEProtocol/creo1message.h>
#include <osSOEProtocol/creo4message.h>
#include <osSOEProtocol/creo3message.h>
#include <osSOEProtocol/creoinitmessage.h>
#include <osSOEProtocol/creo6message.h>
#include <osSOEProtocol/objclosemessage.h>
#include <osSOEProtocol/objlinkmessage.h>
#include <osSOEProtocol/objpreclosemessage.h>
#include <osSOEProtocol/play3message.h>
#include <osSOEProtocol/play6message.h>
#include <osSOEProtocol/play8message.h>
#include <osSOEProtocol/play9message.h>
#include <osSOEProtocol/play9updatemessage.h>
#include <osSOEProtocol/playclosemessage.h>
#include <osSOEProtocol/playinitmessage.h>
#include <osSOEProtocol/playlinkmessage.h>

#include <zthread/Thread.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;

PlayerCreatureObjectProxy::PlayerCreatureObjectProxy()
: CreatureObjectProxy()
{}

void PlayerCreatureObjectProxy::update(uint64 updateTimestamp) 
{
	for (std::vector<boost::shared_ptr<ObjectProxy> >::iterator itor = m_inRange.begin();
		itor != m_inRange.end(); ++itor)
	{
		if ((*itor)->hasMoved())
		{
			printf("Sending movement update for [%s] to [%s]\n", (*itor)->getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue().c_str(), getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue().c_str());
			(*itor)->sendMovementUpdate(m_session);
		}
	}
}

void PlayerCreatureObjectProxy::buildPropertyMap()
{
	if (! m_object)
		createObject();

    const std::string GROUPNAME = "Player";

	CreatureObjectProxy::buildPropertyMap();

	boost::shared_ptr<PlayerCreatureObject> playerCreature = boost::shared_dynamic_cast<PlayerCreatureObject>(m_object);

	addProperty(new Uint64ObjectProperty(
		"GalaxyId", "Galaxy ID", 
		makeFunctor((CBFunctor1<uint64>*)0, *playerCreature, &PlayerCreatureObject::setGalaxyId), 
		makeFunctor((CBFunctor0wRet<uint64>*)0, *playerCreature, &PlayerCreatureObject::getGalaxyId), 
		"Galaxy Id.", 
		GROUPNAME));

	addProperty(new StringObjectProperty(
		"Firstname", "Firstname", 
		makeFunctor((CBFunctor1<std::string>*)0, *playerCreature, &PlayerCreatureObject::setFirstname), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *playerCreature, &PlayerCreatureObject::getFirstname), 
		"Firstname of the player.", 
		GROUPNAME));

	addProperty(new StringObjectProperty(
		"Surname", "Surname", 
		makeFunctor((CBFunctor1<std::string>*)0, *playerCreature, &PlayerCreatureObject::setSurname), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *playerCreature, &PlayerCreatureObject::getSurname), 
		"Surname of the player.", 
		GROUPNAME));

	addProperty(new StringObjectProperty(
		"Hair", "Hair", 
		makeFunctor((CBFunctor1<std::string>*)0, *playerCreature, &PlayerCreatureObject::setHair), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *playerCreature, &PlayerCreatureObject::getHair), 
		"Hair string.", 
		GROUPNAME));

	addProperty(new StringObjectProperty(
		"HairData", "HairData", 
		makeFunctor((CBFunctor1<std::string>*)0, *playerCreature, &PlayerCreatureObject::setHairData), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *playerCreature, &PlayerCreatureObject::getHairData), 
		"Hair data string.", 
		GROUPNAME));

	addProperty(new StringObjectProperty(
		"Biography", "Biography", 
		makeFunctor((CBFunctor1<std::string>*)0, *playerCreature, &PlayerCreatureObject::setBiography), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *playerCreature, &PlayerCreatureObject::getBiography), 
		"Biography string.", 
		GROUPNAME));

	addProperty(new Uint32ObjectProperty(
		"BankCredits", "Bank Credits", 
		makeFunctor((CBFunctor1<uint32>*)0, *playerCreature, &PlayerCreatureObject::setBankCredits), 
		makeFunctor((CBFunctor0wRet<uint32>*)0, *playerCreature, &PlayerCreatureObject::getBankCredits), 
		"Amount of credits in the objects bank.", 
		GROUPNAME));

	addProperty(new Uint32ObjectProperty(
		"InventoryCredits", "Inventory Credits", 
		makeFunctor((CBFunctor1<uint32>*)0, *playerCreature, &PlayerCreatureObject::setInventoryCredits), 
		makeFunctor((CBFunctor0wRet<uint32>*)0, *playerCreature, &PlayerCreatureObject::getInventoryCredits), 
		"Amount of credits in the objects inventory.", 
		GROUPNAME));
}

void PlayerCreatureObjectProxy::createObject()
{
	boost::shared_ptr<PlayerCreatureObject> playerCreature(GS_NEW PlayerCreatureObject);
	m_object = playerCreature;

	buildPropertyMap();
}

void PlayerCreatureObjectProxy::addInRange(boost::shared_ptr<ObjectProxy> object)
{
	ObjectProxy::addInRange(object);
	object->sendReliableUpdate(m_session);
}


void PlayerCreatureObjectProxy::sendInRange(NetworkMessagePtr message)
{
	for (std::vector<boost::shared_ptr<ObjectProxy> >::iterator itor = m_inRange.begin();
		itor != m_inRange.end(); ++itor)
	{
		if ((*itor)->hasSession())
		{	
			(*itor)->getSession()->sendToRemote(message);
		}
	}
}


void PlayerCreatureObjectProxy::sendReliableUpdate(Session* session)
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
	objLink->linkType = ObjLinkMessage::WORLD_LINK;
	session->sendToRemote(objLink);

	if (session == m_session)
	{
		boost::shared_ptr<Creo1Message> creo1(GS_NEW Creo1Message());
		creo1->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		creo1->bankCredits = getPropertyAs<Uint32ObjectProperty*>(std::string("BankCredits"))->getValue();
		creo1->inventoryCredits = getPropertyAs<Uint32ObjectProperty*>(std::string("InventoryCredits"))->getValue();
		session->sendToRemote(creo1);
		
		boost::shared_ptr<Creo4Message> creo4(GS_NEW Creo4Message());
		creo4->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(creo4);
	}

	boost::shared_ptr<Creo3Message> creo3(GS_NEW Creo3Message());
	creo3->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();

	std::string firstname = getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue();
	std::string surname = getPropertyAs<StringObjectProperty*>(std::string("Surname"))->getValue();

    if (surname.c_str() && firstname.c_str())
		creo3->fullname = (std::string)firstname + " " + (std::string)surname;
    else
        creo3->fullname = (std::string)firstname;

	creo3->appearance = getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->getValue();
	creo3->category = getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue();
	creo3->type = getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue();
	creo3->scale = getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->getValue();
	creo3->posture = getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->getValue();
	session->sendToRemote(creo3);

	boost::shared_ptr<Creo6Message> creo6(GS_NEW Creo6Message());
	creo6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	creo6->mood = std::string("none");
	creo6->hair = getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue();
	session->sendToRemote(creo6);

	if (session == m_session)
	{
		boost::shared_ptr<PlayInitMessage> playInit(GS_NEW PlayInitMessage());
		playInit->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(playInit);

		boost::shared_ptr<PlayLinkMessage> playLink(GS_NEW PlayLinkMessage());
		playLink->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(playLink);

		boost::shared_ptr<Play3Message> play3(GS_NEW Play3Message());
		play3->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play3);

		boost::shared_ptr<Play6Message> play6(GS_NEW Play6Message());
		play6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play6);

		boost::shared_ptr<Play8Message> play8(GS_NEW Play8Message());
		play8->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play8);

		boost::shared_ptr<Play9Message> play9(GS_NEW Play9Message());
		play9->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play9);

		boost::shared_ptr<PlayCloseMessage> playClose(GS_NEW PlayCloseMessage());
		playClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(playClose);

		boost::shared_ptr<Play9UpdateMessage> play9Update(GS_NEW Play9UpdateMessage());
		play9Update->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play9Update);
	}

	boost::shared_ptr<ObjPreCloseMessage> objPreClose(GS_NEW ObjPreCloseMessage());
	objPreClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objPreClose);

	boost::shared_ptr<ObjCloseMessage> objClose(GS_NEW ObjCloseMessage());
	objClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objClose);

	if (session == m_session)
	{
		boost::shared_ptr<TangibleObjectProxy> inventory(GS_NEW TangibleObjectProxy);
		inventory->createTemplate();

		inventory->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()+1);
		inventory->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue());
		inventory->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue(std::string("item_n"));
		inventory->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(std::string("inventory"));
		inventory->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(std::string("object/tangible/inventory/shared_character_inventory.iff"));
		inventory->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);

		inventory->setLinkType(ObjLinkMessage::PLAYER_LINK);
		inventory->sendReliableUpdate(session);

		
		boost::shared_ptr<TangibleObjectProxy> bank(GS_NEW TangibleObjectProxy);
		bank->createTemplate();

		bank->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()+4);
		bank->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue());
		bank->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue(std::string("item_n"));
		bank->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(std::string("bank"));
		bank->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(std::string("object/tangible/bank/shared_character_bank.iff"));
		bank->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);

		bank->setLinkType(ObjLinkMessage::PLAYER_LINK);
		bank->sendReliableUpdate(session);

		
		boost::shared_ptr<TangibleObjectProxy> datapad(GS_NEW TangibleObjectProxy);
		datapad->createTemplate();

		datapad->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()+3);
		datapad->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue());
		datapad->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue(std::string("item_n"));
		datapad->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(std::string("datapad"));
		datapad->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(std::string("object/tangible/datapad/shared_character_datapad.iff"));
		datapad->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);

		datapad->setLinkType(ObjLinkMessage::PLAYER_LINK);
		datapad->sendReliableUpdate(session);
	}

	boost::shared_ptr<TangibleObjectProxy> hair(GS_NEW TangibleObjectProxy);
	hair->createTemplate();
	
	hair->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()+8);
	hair->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue());
	hair->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue(std::string("hair_name"));
	hair->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(std::string("hair"));
	hair->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue());
	hair->getPropertyAs<StringObjectProperty*>(std::string("Color"))->setValue(getPropertyAs<StringObjectProperty*>(std::string("HairData"))->getValue());
	hair->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);

	hair->setLinkType(ObjLinkMessage::PLAYER_LINK);
	hair->sendReliableUpdate(session);

	for (std::vector<boost::shared_ptr<TangibleObjectProxy> >::iterator i = m_items.begin();
		i != m_items.end(); ++i)
	{
		if ((*i)->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->getValue())
		{
			(*i)->sendReliableUpdate(session);
		}
	}
}

void PlayerCreatureObjectProxy::store()
{
	try
    {
		
		mysqlpp::Query q = Datastore::getStationDB().query();

		q << "SELECT characters.id "
		  << "FROM characters "
		  << "WHERE object_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		
        mysqlpp::Result result = q.store();
                
		if (result)
        {
			mysqlpp::Row row = result.fetch_row();

		mysqlpp::Query q = Datastore::getStationDB().query();

		q << "UPDATE `characters` "
          << "SET galaxy_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("GalaxyId"))->getValue()  << " , "
		  << " zone_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ZoneId"))->getValue()  << " , "
		  << " cell_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->getValue()  << " , "
		  << " object_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()  << " , "
          << " firstname = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue() << " , "
          << " surname = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Surname"))->getValue() << " , "
		  << " model = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue() << " , "
		  << " category = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue() << " , "
		  << " type = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue() << " , "
		  << " appearance = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->getValue() << " , "
		  << " hair = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue() << " , "
		  << " hair_data = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("HairData"))->getValue() << " , "
		  << " biography = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Biography"))->getValue() << " , "
		  << " mood = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Mood"))->getValue() << " , "
		  << " planet = " << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Planet"))->getValue() << " , "
		  << " credits_bank = " << getPropertyAs<Uint32ObjectProperty*>(std::string("BankCredits"))->getValue() << " , "
		  << " credits_inventory = " << getPropertyAs<Uint32ObjectProperty*>(std::string("InventoryCredits"))->getValue() << " , "
          << " quaternion_x = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->getValue() << " , "
          << " quaternion_y = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->getValue() << " , "
          << " quaternion_z = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->getValue() << " , "
          << " quaternion_w = " << getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->getValue() << " , "
          << " position_x = " << getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue() << " , "
          << " position_y = " << getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue() << " , "
          << " position_z = " << getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue() << " , "
          << " scale = " << getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->getValue() << " , "
          << " state = " << getPropertyAs<UintObjectProperty*>(std::string("State"))->getValue() << "  "
		  << "WHERE characters.id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->getValue() << " LIMIT 1";
		
		mysqlpp::ResNSel result = q.execute();
          
		if (! result.success)
        {
			Log::getMainLog().error("Unable to update player character.");
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
		mysqlpp::Query q = Datastore::getStationDB().query();

        q << "INSERT INTO `characters` (`galaxy_id`,`zone_id`, `cell_id`, `object_id`, `firstname`, "
		  << "  `surname`, `model`, `category`, `type`, `appearance`, `hair`, `hair_data`, `biography`, "
		  << "  `mood`, `credits_bank`, `credits_inventory`, "
          << "  `quaternion_x`, `quaternion_y`, `quaternion_z`, `quaternion_w`, "
          << "  `position_x`, `position_y`, `position_z`, "
          << "  `scale`, `created_on`, `state`) "
		  << "VALUES (" << getPropertyAs<Uint64ObjectProperty*>(std::string("GalaxyId"))->getValue() << ", " 
          << getPropertyAs<Uint64ObjectProperty*>(std::string("ZoneId"))->getValue() << ", " 
          << getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->getValue() << ", " 
          << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Surname"))->getValue() << ", "
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue() << ", "
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue() << ", "
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("HairData"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Biography"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Mood"))->getValue() << ", " 
		  << mysqlpp::quote << getPropertyAs<StringObjectProperty*>(std::string("Planet"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("BankCredits"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("InventoryCredits"))->getValue() << ", " 
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
			Log::getMainLog().error("Unable to create new player character entry.");
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


void PlayerCreatureObjectProxy::loadFromDatabaseId(uint64 databaseId)
{
	createObject();

	try
    {
		mysqlpp::Query q = Datastore::getStationDB().query();

		q << "SELECT characters.id, "
          << "       characters.account_id, "
		  << "		 characters.galaxy_id, "
          << "       characters.zone_id, "
		  << "	     characters.cell_id, "
          << "       characters.object_id, "
          << "       characters.firstname, "
          << "       characters.surname, "
		  << "		 characters.model, "
		  << "		 characters.category, "
		  << "		 characters.type, "
          << "       characters.appearance, "
          << "       characters.hair, "
          << "       characters.hair_data, "
          << "       characters.biography, "
          << "       characters.mood, "
          << "       characters.planet, "
          << "       characters.credits_bank, "
          << "       characters.credits_inventory, "
          << "       characters.quaternion_x, "
          << "       characters.quaternion_y, "
          << "       characters.quaternion_z, "
          << "       characters.quaternion_w, "
          << "       characters.position_x, "
          << "       characters.position_y, "
          << "       characters.position_z, "
          << "       characters.scale, "
          << "       characters.state "
          << "FROM characters "
          << "WHERE characters.id = " << databaseId << " LIMIT 1";

        mysqlpp::Result result = q.store();
                
		if (result)
        {
			mysqlpp::Row row = result.fetch_row();
			
			getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64)row["id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("GalaxyId"))->setValue((uint64)row["galaxy_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64)row["object_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64)row["cell_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ZoneId"))->setValue((uint64)row["zone_id"]);
			getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->setValue((std::string)row["firstname"]);
			getPropertyAs<StringObjectProperty*>(std::string("Surname"))->setValue((std::string)row["surname"]);
			getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->setValue((std::string)row["appearance"]);
			getPropertyAs<StringObjectProperty*>(std::string("Hair"))->setValue((std::string)row["hair"]);
			getPropertyAs<StringObjectProperty*>(std::string("HairData"))->setValue((std::string)row["hair_data"]);
			getPropertyAs<StringObjectProperty*>(std::string("Biography"))->setValue((std::string)row["biography"]);
			getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)row["model"]);
			getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)row["category"]);
			getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)row["type"]);
			getPropertyAs<StringObjectProperty*>(std::string("Planet"))->setValue((std::string)row["planet"]);
			getPropertyAs<StringObjectProperty*>(std::string("Mood"))->setValue((std::string)row["mood"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("BankCredits"))->setValue((uint32)row["credits_bank"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("InventoryCredits"))->setValue((uint32)row["credits_inventory"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)row["quaternion_x"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)row["quaternion_y"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)row["quaternion_z"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)row["quaternion_w"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)row["position_x"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)row["position_y"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)row["position_z"]);
			getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)row["scale"]);
			getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint)row["state"]);

			loadItems();
        }
        
		else
        {
            Log::getMainLog().error("Failed to load player character: 0x%08x", databaseId);
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


void PlayerCreatureObjectProxy::loadItems()
{
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT character_items.id "
          << "FROM character_items "
          << "WHERE character_items.character_id = " << getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();

        mysqlpp::Result result = q.store();
                
		if (result)
        {
            mysqlpp::Row row;
            while (row = result.fetch_row())
            {
				boost::shared_ptr<TangibleObjectProxy> item(GS_NEW TangibleObjectProxy);
				item->loadFromDatabaseId((uint32)row["id"]);
				item->setLinkType(ObjLinkMessage::PLAYER_LINK);
				m_items.push_back(item);
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
	}	
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		Log::getMainLog().error("Error: %s", er.what());
		return;
	}
}		
void PlayerCreatureObjectProxy::setPlayerSession(gsServer::Session* session)
{
	m_session = session;

	boost::shared_ptr<SettingUnk1Message> settingUnk1(GS_NEW SettingUnk1Message());
	session->sendToRemote(settingUnk1);

	boost::shared_ptr<UnkInt900Message> unkint900(GS_NEW UnkInt900Message());
	session->sendToRemote(unkint900);

	boost::shared_ptr<LoadTerrainMessage> loadTerrain(GS_NEW LoadTerrainMessage());
	loadTerrain->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	loadTerrain->terrain = std::string("terrain/"+getPropertyAs<StringObjectProperty*>(std::string("Planet"))->getValue()+"naboo.trn");
	loadTerrain->positionX = getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue();
	loadTerrain->positionY = getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue();
	loadTerrain->positionZ = getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue();
	loadTerrain->sharedModel = getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue();
	loadTerrain->zoneId = getPropertyAs<Uint64ObjectProperty*>(std::string("ZoneId"))->getValue();
	session->sendToRemote(loadTerrain);

	boost::shared_ptr<TimeUpdateMessage> timeUpdate(GS_NEW TimeUpdateMessage());
	//timeUpdate->time = time(0);
	session->sendToRemote(timeUpdate);

	sendReliableUpdate(session);
}

