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

#include "osSOEProtocol/playercreatureobjectproxy.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/macros.h>
#include <gsServer/session.h>
#include <gsCore/datastore.h>
#include <osSOEProtocol/objectpropertytypes.h>
#include <osSOEProtocol/playercreatureobject.h>

#include <osSOEProtocol/settingunk1message.h>
#include <osSOEProtocol/unkint900message.h>
#include <osSOEProtocol/loadterrainmessage.h>
#include <osSOEProtocol/timeupdatemessage.h>
#include <osSOEProtocol/factionupdatemessage.h>
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

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

PlayerCreatureObjectProxy::PlayerCreatureObjectProxy()
: CreatureObjectProxy()
{}

void PlayerCreatureObjectProxy::update(uint64_t updateTimestamp) 
{
	for (std::vector<std::shared_ptr<ObjectProxy> >::iterator itor = m_inRange.begin();
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

    std::shared_ptr<PlayerCreatureObject> playerCreature = std::dynamic_pointer_cast<PlayerCreatureObject>(m_object);

	addProperty(new Uint64ObjectProperty(
		"GalaxyId", "Galaxy ID", 
		makeFunctor((CBFunctor1<uint64_t>*)0, *playerCreature, &PlayerCreatureObject::setGalaxyId), 
		makeFunctor((CBFunctor0wRet<uint64_t>*)0, *playerCreature, &PlayerCreatureObject::getGalaxyId), 
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
		makeFunctor((CBFunctor1<uint32_t>*)0, *playerCreature, &PlayerCreatureObject::setBankCredits), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *playerCreature, &PlayerCreatureObject::getBankCredits), 
		"Amount of credits in the objects bank.", 
		GROUPNAME));

	addProperty(new Uint32ObjectProperty(
		"InventoryCredits", "Inventory Credits", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *playerCreature, &PlayerCreatureObject::setInventoryCredits), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *playerCreature, &PlayerCreatureObject::getInventoryCredits), 
		"Amount of credits in the objects inventory.", 
		GROUPNAME));
}

void PlayerCreatureObjectProxy::createObject()
{
	std::shared_ptr<PlayerCreatureObject> playerCreature(GS_NEW PlayerCreatureObject);
	m_object = playerCreature;

	buildPropertyMap();
}

void PlayerCreatureObjectProxy::addInRange(std::shared_ptr<ObjectProxy> object)
{
	ObjectProxy::addInRange(object);
	object->sendReliableUpdate(m_session);
}


void PlayerCreatureObjectProxy::sendInRange(NetworkMessagePtr message)
{
	for (std::vector<std::shared_ptr<ObjectProxy> >::iterator itor = m_inRange.begin();
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
	std::shared_ptr<CreoInitMessage> creoInit(GS_NEW CreoInitMessage());
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
	std::shared_ptr<ObjLinkMessage> objLink(GS_NEW ObjLinkMessage());
	objLink->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	objLink->parentId = getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->getValue();
	objLink->linkType = ObjLinkMessage::WORLD_LINK;
	session->sendToRemote(objLink);

	if (session == m_session)
	{
		std::shared_ptr<Creo1Message> creo1(GS_NEW Creo1Message());
		creo1->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		creo1->bankCredits = getPropertyAs<Uint32ObjectProperty*>(std::string("BankCredits"))->getValue();
		creo1->inventoryCredits = getPropertyAs<Uint32ObjectProperty*>(std::string("InventoryCredits"))->getValue();
		
		creo1->healthModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("HealthModifiers"))->getValue();
		creo1->strengthModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("StrengthModifiers"))->getValue();
		creo1->constitutionModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("ConstitutionModifiers"))->getValue();
		creo1->actionModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("ActionModifiers"))->getValue();
		creo1->quicknessModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("QuicknessModifiers"))->getValue();
		creo1->staminaModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("StaminaModifiers"))->getValue();
		creo1->mindModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("MindModifiers"))->getValue();
		creo1->focusModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("FocusModifiers"))->getValue();
		creo1->willpowerModifiers = getPropertyAs<Uint32ObjectProperty*>(std::string("WillpowerModifiers"))->getValue();

		session->sendToRemote(creo1);
		
		std::shared_ptr<Creo4Message> creo4(GS_NEW Creo4Message());
		creo4->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(creo4);
	}

	std::shared_ptr<Creo3Message> creo3(GS_NEW Creo3Message());
	creo3->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	creo3->targetId = getPropertyAs<Uint64ObjectProperty*>(std::string("TargetId"))->getValue();

	std::string firstname = getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue();
	std::string surname = getPropertyAs<StringObjectProperty*>(std::string("Surname"))->getValue();

    if (surname.c_str() && firstname.c_str())
		creo3->fullname = (std::string)firstname + " " + (std::string)surname;
    else
        creo3->fullname = (std::string)firstname;

	creo3->appearance = getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->getValue();
	creo3->category = getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue();
	creo3->type = getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue();
	creo3->battleFatigue = getPropertyAs<Uint32ObjectProperty*>(std::string("BattleFatigue"))->getValue();
	creo3->scale = getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->getValue();
	creo3->posture = getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->getValue();
	
	creo3->healthWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("HealthWounds"))->getValue();
	creo3->strengthWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("StrengthWounds"))->getValue();
	creo3->constitutionWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("ConstitutionWounds"))->getValue();
	creo3->actionWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("ActionWounds"))->getValue();
	creo3->quicknessWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("QuicknessWounds"))->getValue();
	creo3->staminaWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("StaminaWounds"))->getValue();
	creo3->mindWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("MindWounds"))->getValue();
	creo3->focusWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("FocusWounds"))->getValue();
	creo3->willpowerWounds = getPropertyAs<Uint32ObjectProperty*>(std::string("WillpowerWounds"))->getValue();

	session->sendToRemote(creo3);

	std::shared_ptr<Creo6Message> creo6(GS_NEW Creo6Message());
	creo6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	creo6->mood = getPropertyAs<StringObjectProperty*>(std::string("Mood"))->getValue();
	creo6->hair = getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue();
	creo6->maxHealth = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxHealth"))->getValue();
	creo6->maxStrength = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStrength"))->getValue();
	creo6->maxConstitution = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxConstitution"))->getValue();
	creo6->maxAction = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxAction"))->getValue();
	creo6->maxQuickness = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxQuickness"))->getValue();
	creo6->maxStamina = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStamina"))->getValue();
	creo6->maxMind = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxMind"))->getValue();
	creo6->maxFocus = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxFocus"))->getValue();
	creo6->maxWillpower = getPropertyAs<Uint32ObjectProperty*>(std::string("MaxWillpower"))->getValue();
	
	creo6->currentHealth = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentHealth"))->getValue();
	creo6->currentStrength = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentStrength"))->getValue();
	creo6->currentConstitution = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentConstitution"))->getValue();
	creo6->currentAction = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentAction"))->getValue();
	creo6->currentQuickness = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentQuickness"))->getValue();
	creo6->currentStamina = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentStamina"))->getValue();
	creo6->currentMind = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentMind"))->getValue();
	creo6->currentFocus = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentFocus"))->getValue();
	creo6->currentWillpower = getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentWillpower"))->getValue();

	session->sendToRemote(creo6);

	if (session == m_session)
	{
		std::shared_ptr<PlayInitMessage> playInit(GS_NEW PlayInitMessage());
		playInit->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(playInit);

		std::shared_ptr<PlayLinkMessage> playLink(GS_NEW PlayLinkMessage());
		playLink->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(playLink);

		std::shared_ptr<Play3Message> play3(GS_NEW Play3Message());
		play3->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play3);

		std::shared_ptr<Play6Message> play6(GS_NEW Play6Message());
		play6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play6);

		std::shared_ptr<Play8Message> play8(GS_NEW Play8Message());
		play8->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play8);

		std::shared_ptr<Play9Message> play9(GS_NEW Play9Message());
		play9->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play9);

		std::shared_ptr<PlayCloseMessage> playClose(GS_NEW PlayCloseMessage());
		playClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(playClose);

		std::shared_ptr<Play9UpdateMessage> play9Update(GS_NEW Play9UpdateMessage());
		play9Update->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
		session->sendToRemote(play9Update);
	}

	std::shared_ptr<ObjPreCloseMessage> objPreClose(GS_NEW ObjPreCloseMessage());
	objPreClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objPreClose);

	std::shared_ptr<ObjCloseMessage> objClose(GS_NEW ObjCloseMessage());
	objClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objClose);

	if (session == m_session)
	{
		std::shared_ptr<TangibleObjectProxy> inventory(GS_NEW TangibleObjectProxy);
		inventory->createTemplate();

		inventory->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()+1);
		inventory->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue());
		inventory->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue(std::string("item_n"));
		inventory->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(std::string("inventory"));
		inventory->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(std::string("object/tangible/inventory/shared_character_inventory.iff"));
		inventory->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);

		inventory->setLinkType(ObjLinkMessage::PLAYER_LINK);
		inventory->sendReliableUpdate(session);

		
		std::shared_ptr<TangibleObjectProxy> bank(GS_NEW TangibleObjectProxy);
		bank->createTemplate();

		bank->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue()+4);
		bank->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue());
		bank->getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue(std::string("item_n"));
		bank->getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue(std::string("bank"));
		bank->getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue(std::string("object/tangible/bank/shared_character_bank.iff"));
		bank->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);

		bank->setLinkType(ObjLinkMessage::PLAYER_LINK);
		bank->sendReliableUpdate(session);

		
		std::shared_ptr<TangibleObjectProxy> datapad(GS_NEW TangibleObjectProxy);
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

	std::shared_ptr<TangibleObjectProxy> hair(GS_NEW TangibleObjectProxy);
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

	for (std::vector<std::shared_ptr<TangibleObjectProxy> >::iterator i = m_items.begin();
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
		
        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {

		    q = Datastore::getStationDB().query();

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
		      << " health = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxHealth"))->getValue() << ", " 
		      << " strength = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStrength"))->getValue() << ", " 
		      << " constitution = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxConstitution"))->getValue() << ", " 
		      << " action = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxAction"))->getValue() << ", " 
		      << " quickness = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxQuickness"))->getValue() << ", " 
		      << " stamina = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStamina"))->getValue() << ", " 
		      << " mind = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxMind"))->getValue() << ", " 
		      << " focus = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxFocus"))->getValue() << ", " 
		      << " willpower = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxWillpower"))->getValue() << ", " 
		      
		      << " health_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("HealthWounds"))->getValue() << ", " 			  		  
		      << " strength_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("StrengthWounds"))->getValue() << ", " 
		      << " constitution_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("ConstitutionWounds"))->getValue() << ", " 
		      << " action_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("ActionWounds"))->getValue() << ", " 
		      << " quickness_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("QuicknessWounds"))->getValue() << ", " 
		      << " stamina_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("StaminaWounds"))->getValue() << ", " 
		      << " mind_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("MindWounds"))->getValue() << ", " 
		      << " focus_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("FocusWounds"))->getValue() << ", " 
		      << " willpower_wounds = " << getPropertyAs<Uint32ObjectProperty*>(std::string("WillpowerWounds"))->getValue() << ", " 
		      << " battle_fatigue = " << getPropertyAs<Uint32ObjectProperty*>(std::string("BattleFatigue"))->getValue() << ", " 
		      << " creature_type = " << getPropertyAs<Uint32ObjectProperty*>(std::string("CreatureType"))->getValue() << ", " 
		      << " faction_alignment = " << getPropertyAs<Uint32ObjectProperty*>(std::string("FactionAlignment"))->getValue() << ", " 
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
		    
		    if (! q.execute())
            {
		    	LOG(ERROR) << "Unable to update player character.";
		    	return;
            }
        }
        else
		// Continue normally.
		q = Datastore::getStationDB().query();

        q << "INSERT INTO `characters` (`galaxy_id`,`zone_id`, `cell_id`, `object_id`, `firstname`, "
		  << "  `surname`, `model`, `category`, `type`, `appearance`, `hair`, `hair_data`, `biography`, "
		  << "  `health`, `strength`, `constitution`, `action`, `quickness`, "
		  << "  `stamina`, `mind`, `focus`, `willpower`, "
		  << "  `health_wounds`, `strength_wounds`, `constitution_wounds`, `action_wounds`, `quickness_wounds`, "
		  << "  `stamina_wounds`, `mind_wounds`, `focus_wounds`, `willpower_wounds`, "
		  << "  `battle_fatigue`, `creature_type`, `faction_alignment`, "
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
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxHealth"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStrength"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxConstitution"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxAction"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxQuickness"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStamina"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxMind"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxFocus"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MaxWillpower"))->getValue() << ", " 			
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("BattleFatigue"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("HealthWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("StrengthWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("ConstitutionWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("ActionWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("QuicknessWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("StaminaWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("MindWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("FocusWounds"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("WillpowerWounds"))->getValue() << ", " 			
		  
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("CreatureType"))->getValue() << ", " 
		  << getPropertyAs<Uint32ObjectProperty*>(std::string("FactionAlignment"))->getValue() << ", " 
			
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

		if (! q.execute())
        {
            LOG(ERROR) << "Unable to create new player character entry.";
			return;
        }
	}
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		LOG(ERROR) << "ERROR: " << er.what();
		return;
	}
}


void PlayerCreatureObjectProxy::loadFromDatabaseId(uint64_t databaseId)
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
          << "       characters.health, "
          << "       characters.strength, "
          << "       characters.constitution, "
          << "       characters.action, "
          << "       characters.quickness, "
          << "       characters.stamina, "
          << "       characters.mind, "
          << "       characters.focus, "
          << "       characters.willpower, "
          << "       characters.health_wounds, "
          << "       characters.strength_wounds, "
          << "       characters.constitution_wounds, "
          << "       characters.action_wounds, "
          << "       characters.quickness_wounds, "
          << "       characters.stamina_wounds, "
          << "       characters.mind_wounds, "
          << "       characters.focus_wounds, "
          << "       characters.willpower_wounds, "
          << "       characters.battle_fatigue, "
          << "       characters.creature_type, "
          << "       characters.faction_alignment, "
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

        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {			
			getPropertyAs<Uint64ObjectProperty*>(std::string("DatabaseId"))->setValue((uint64_t)result[0]["id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("GalaxyId"))->setValue((uint64_t)result[0]["galaxy_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue((uint64_t)result[0]["object_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue((uint64_t)result[0]["cell_id"]);
			getPropertyAs<Uint64ObjectProperty*>(std::string("ZoneId"))->setValue((uint64_t)result[0]["zone_id"]);
			getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->setValue((std::string)result[0]["firstname"]);
			getPropertyAs<StringObjectProperty*>(std::string("Surname"))->setValue((std::string)result[0]["surname"]);
			getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->setValue((std::string)result[0]["appearance"]);
			getPropertyAs<StringObjectProperty*>(std::string("Hair"))->setValue((std::string)result[0]["hair"]);
			getPropertyAs<StringObjectProperty*>(std::string("HairData"))->setValue((std::string)result[0]["hair_data"]);
			getPropertyAs<StringObjectProperty*>(std::string("Biography"))->setValue((std::string)result[0]["biography"]);
			getPropertyAs<StringObjectProperty*>(std::string("Model"))->setValue((std::string)result[0]["model"]);
			getPropertyAs<StringObjectProperty*>(std::string("Category"))->setValue((std::string)result[0]["category"]);
			getPropertyAs<StringObjectProperty*>(std::string("Type"))->setValue((std::string)result[0]["type"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxHealth"))->setValue((uint32_t)result[0]["health"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStrength"))->setValue((uint32_t)result[0]["strength"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxConstitution"))->setValue((uint32_t)result[0]["constitution"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxAction"))->setValue((uint32_t)result[0]["action"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxQuickness"))->setValue((uint32_t)result[0]["quickness"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxStamina"))->setValue((uint32_t)result[0]["stamina"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxMind"))->setValue((uint32_t)result[0]["mind"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxFocus"))->setValue((uint32_t)result[0]["focus"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MaxWillpower"))->setValue((uint32_t)result[0]["willpower"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentHealth"))->setValue((uint32_t)result[0]["health"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentStrength"))->setValue((uint32_t)result[0]["strength"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentConstitution"))->setValue((uint32_t)result[0]["constitution"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentAction"))->setValue((uint32_t)result[0]["action"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentQuickness"))->setValue((uint32_t)result[0]["quickness"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentStamina"))->setValue((uint32_t)result[0]["stamina"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentMind"))->setValue((uint32_t)result[0]["mind"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentFocus"))->setValue((uint32_t)result[0]["focus"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CurrentWillpower"))->setValue((uint32_t)result[0]["willpower"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("HealthWounds"))->setValue((uint32_t)result[0]["health_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("StrengthWounds"))->setValue((uint32_t)result[0]["strength_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("ConstitutionWounds"))->setValue((uint32_t)result[0]["constitution_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("ActionWounds"))->setValue((uint32_t)result[0]["action_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("QuicknessWounds"))->setValue((uint32_t)result[0]["quickness_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("StaminaWounds"))->setValue((uint32_t)result[0]["stamina_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MindWounds"))->setValue((uint32_t)result[0]["mind_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("FocusWounds"))->setValue((uint32_t)result[0]["focus_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("WillpowerWounds"))->setValue((uint32_t)result[0]["willpower_wounds"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("HealthModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("StrengthModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("ConstitutionModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("ActionModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("QuicknessModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("StaminaModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("MindModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("FocusModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("WillpowerModifiers"))->setValue(0);
			getPropertyAs<Uint32ObjectProperty*>(std::string("BattleFatigue"))->setValue((uint32_t)result[0]["battle_fatigue"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("CreatureType"))->setValue((uint32_t)result[0]["creature_type"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("FactionAlignment"))->setValue((uint32_t)result[0]["faction_alignment"]);
			
			getPropertyAs<StringObjectProperty*>(std::string("Planet"))->setValue((std::string)result[0]["planet"]);
			getPropertyAs<StringObjectProperty*>(std::string("Mood"))->setValue((std::string)result[0]["mood"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("BankCredits"))->setValue((uint32_t)result[0]["credits_bank"]);
			getPropertyAs<Uint32ObjectProperty*>(std::string("InventoryCredits"))->setValue((uint32_t)result[0]["credits_inventory"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue((float)result[0]["quaternion_x"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue((float)result[0]["quaternion_y"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue((float)result[0]["quaternion_z"]);
			getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue((float)result[0]["quaternion_w"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue((float)result[0]["position_x"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue((float)result[0]["position_y"]);
			getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue((float)result[0]["position_z"]);
			getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->setValue((float)result[0]["scale"]);
			getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue((uint32_t)result[0]["state"]);

			loadItems();
        }
        
		else
        {
            LOG(ERROR) << "Failed to load player character: " << std::hex << databaseId;
        }
    }
	
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		LOG(ERROR) << "ERROR: " << er.what();
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

        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        { 
            std::for_each(begin(result), end(result), [this] (const mysqlpp::Row& row) 
            { 
				std::shared_ptr<TangibleObjectProxy> item(GS_NEW TangibleObjectProxy);
				item->loadFromDatabaseId((uint32_t)row["id"]);
				item->setLinkType(ObjLinkMessage::PLAYER_LINK);
				m_items.push_back(item);
            });
		}
	}
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
		LOG(ERROR) << "ERROR: " << er.what();
		return;
	}
}		
void PlayerCreatureObjectProxy::setPlayerSession(gsServer::Session* session)
{
	m_session = session;

	std::shared_ptr<SettingUnk1Message> settingUnk1(GS_NEW SettingUnk1Message());
	session->sendToRemote(settingUnk1);

	std::shared_ptr<UnkInt900Message> unkint900(GS_NEW UnkInt900Message());
	session->sendToRemote(unkint900);

	std::shared_ptr<LoadTerrainMessage> loadTerrain(GS_NEW LoadTerrainMessage());
	loadTerrain->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	loadTerrain->terrain = std::string("terrain/"+getPropertyAs<StringObjectProperty*>(std::string("Planet"))->getValue()+".trn");
	loadTerrain->positionX = getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue();
	loadTerrain->positionY = getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue();
	loadTerrain->positionZ = getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue();
	loadTerrain->sharedModel = getPropertyAs<StringObjectProperty*>(std::string("Model"))->getValue();
	loadTerrain->zoneId = getPropertyAs<Uint64ObjectProperty*>(std::string("ZoneId"))->getValue();
	session->sendToRemote(loadTerrain);

	std::shared_ptr<TimeUpdateMessage> timeUpdate(GS_NEW TimeUpdateMessage());
	//timeUpdate->time = time(0);
	session->sendToRemote(timeUpdate);

	sendReliableUpdate(session);
}

