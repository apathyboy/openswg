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

#include "osSOEProtocol/creatureobjectproxy.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <gsCore/macros.h>
#include <gsServer/session.h>
#include <gsCore/datastore.h>
#include <osSOEProtocol/objectpropertytypes.h>
#include <osSOEProtocol/playercreatureobject.h>
#include <osSOEProtocol/playercreatureobjectproxy.h>

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

#include <osSOEProtocol/creatureobject.h>
#include <osSOEProtocol/objectpropertytypes.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;

CreatureObjectProxy::CreatureObjectProxy()
: ObjectProxy()
{}

void CreatureObjectProxy::createTemplate()
{
	createObject();
}

void CreatureObjectProxy::createObject()
{
	std::shared_ptr<CreatureObject> creature(GS_NEW CreatureObject);
	m_object = creature;

	buildPropertyMap();
}

void CreatureObjectProxy::buildPropertyMap()
{
	ObjectProxy::buildPropertyMap();

    const std::string GROUPNAME = "Creature";

    std::shared_ptr<CreatureObject> creature = std::dynamic_pointer_cast<CreatureObject>(m_object);

	addProperty(new StringObjectProperty(
		"Appearance", "Appearance", 
        std::bind(&CreatureObject::setAppearance, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getAppearance, creature),
		"Appearance string of the creature object. Note that in the future this will be expanded to include modification of the individual items of the appearance string.", 
		GROUPNAME));
	
	addProperty(new Uint8ObjectProperty(
		"Posture", "Posture", 
        std::bind(&CreatureObject::setPosture, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getPosture, creature),
		"Posture of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint64ObjectProperty(
		"TargetId", "Target Id", 
        std::bind(&CreatureObject::setTargetId, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getTargetId, creature),
		"Target id of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxHealth", "Max Health", 
        std::bind(&CreatureObject::setMaxHealth, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxHealth, creature),
		"Max health of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxStrength", "Max Strength", 
        std::bind(&CreatureObject::setMaxStrength, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxStrength, creature),
		"Max strength of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxConstitution", "Max Constitution", 
        std::bind(&CreatureObject::setMaxConstitution, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxConstitution, creature),
		"Max constitution of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxAction", "Max Action", 
        std::bind(&CreatureObject::setMaxAction, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxAction, creature),
		"Max action of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxQuickness", "Max Quickness", 
        std::bind(&CreatureObject::setMaxQuickness, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxQuickness, creature),
		"Max quickness of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxStamina", "Max Stamina", 
        std::bind(&CreatureObject::setMaxStamina, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxStamina, creature),
		"Max stamina of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxMind", "Max Mind", 
        std::bind(&CreatureObject::setMaxMind, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxMind, creature),
		"Max mind of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxFocus", "Max Focus", 
        std::bind(&CreatureObject::setMaxFocus, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxFocus, creature),
		"Max focus of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxWillpower", "Max Willpower", 
        std::bind(&CreatureObject::setMaxWillpower, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMaxWillpower, creature),
		"Max willpower of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentHealth", "Current Health", 
        std::bind(&CreatureObject::setCurrentHealth, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentHealth, creature),
		"Current health of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentStrength", "Current Strength", 
        std::bind(&CreatureObject::setCurrentStrength, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentStrength, creature),
		"Current strength of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentConstitution", "Current Constitution", 
        std::bind(&CreatureObject::setCurrentConstitution, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentConstitution, creature),
		"Current constitution of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentAction", "Current Action", 
        std::bind(&CreatureObject::setCurrentAction, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentAction, creature),
		"Current action of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentQuickness", "Current Quickness", 
        std::bind(&CreatureObject::setCurrentQuickness, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentQuickness, creature), 
		"Current quickness of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentStamina", "Current Stamina", 
        std::bind(&CreatureObject::setCurrentStamina, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentStamina, creature),
		"Current stamina of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentMind", "Current Mind", 
        std::bind(&CreatureObject::setCurrentMind, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentMind, creature),
		"Current mind of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentFocus", "Current Focus", 
        std::bind(&CreatureObject::setCurrentFocus, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentFocus, creature),
		"Max focus of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentWillpower", "Current Willpower", 
        std::bind(&CreatureObject::setCurrentWillpower, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCurrentWillpower, creature),
		"Current willpower of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"HealthWounds", "HealthWounds", 
        std::bind(&CreatureObject::setHealthWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getHealthWounds, creature),
		"Health wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StrengthWounds", "StrengthWounds", 
        std::bind(&CreatureObject::setStrengthWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getStrengthWounds, creature), 
		"Strength wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ConstitutionWounds", "Constitution Wounds", 
        std::bind(&CreatureObject::setConstitutionWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getConstitutionWounds, creature),
		"Constitution wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ActionWounds", "Action Wounds", 
        std::bind(&CreatureObject::setActionWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getActionWounds, creature),
		"Action wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"QuicknessWounds", "QuicknessWounds", 
        std::bind(&CreatureObject::setQuicknessWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getQuicknessWounds, creature),
		"Quickness wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StaminaWounds", "Stamina Wounds", 
        std::bind(&CreatureObject::setStaminaWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getStaminaWounds, creature),
		"Stamina wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MindWounds", "MindWounds", 
        std::bind(&CreatureObject::setMindWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMindWounds, creature),
		"Mind wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"FocusWounds", "Focus Wounds", 
        std::bind(&CreatureObject::setFocusWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getFocusWounds, creature),
		"Focus wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"WillpowerWounds", "Willpower Wounds", 
        std::bind(&CreatureObject::setWillpowerWounds, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getWillpowerWounds, creature),
		"Willpower wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"HealthModifiers", "Health Modifiers", 
        std::bind(&CreatureObject::setHealthModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getHealthModifiers, creature),
		"Health modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StrengthModifiers", "Strength Modifiers", 
        std::bind(&CreatureObject::setStrengthModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getStrengthModifiers, creature),
		"Strength modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ConstitutionModifiers", "Constitution Modifiers", 
        std::bind(&CreatureObject::setConstitutionModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getConstitutionModifiers, creature), 
		"Constitution modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ActionModifiers", "Action modifiers", 
        std::bind(&CreatureObject::setActionModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getActionModifiers, creature),
		"Action modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"QuicknessModifiers", "Quickness Modifiers", 
        std::bind(&CreatureObject::setQuicknessModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getQuicknessModifiers, creature),
		"Quickness modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StaminaModifiers", "Stamina Modifiers", 
        std::bind(&CreatureObject::setStaminaModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getStaminaModifiers, creature),
		"Stamina modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MindModifiers", "Mind Modifiers", 
        std::bind(&CreatureObject::setMindModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMindModifiers, creature),
		"Mind modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"FocusModifiers", "Focus Modifiers", 
        std::bind(&CreatureObject::setFocusModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getFocusModifiers, creature),
		"Focus modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"WillpowerModifiers", "Willpower Modifiers", 
        std::bind(&CreatureObject::setWillpowerModifiers, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getWillpowerModifiers, creature),
		"Willpower modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CreatureType", "Creature Type", 
        std::bind(&CreatureObject::setCreatureType, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getCreatureType, creature),
		"Creature type of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"FactionAlignment", "Faction Alignment", 
        std::bind(&CreatureObject::setFactionAlignment, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getFactionAlignment, creature),
		"Faction alignment of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"BattleFatigue", "Battle Fatigue", 
        std::bind(&CreatureObject::setBattleFatigue, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getBattleFatigue, creature),
		"Battle fatigue of the creature object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Mood", "Mood", 
        std::bind(&CreatureObject::setMood, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getMood, creature),
		"Mood of the creature object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Planet", "Planet", 
        std::bind(&CreatureObject::setPlanet, creature, std::placeholders::_1), 
        std::bind(&CreatureObject::getPlanet, creature),
		"Planet where the creature is currently located.", 
		GROUPNAME));
}

void CreatureObjectProxy::sendReliableUpdate(Session* session)
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

	std::shared_ptr<Creo3Message> creo3(GS_NEW Creo3Message());
	creo3->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();

//	std::string firstname = getPropertyAs<StringObjectProperty*>(std::string("Firstname"))->getValue();
//	std::string surname = getPropertyAs<StringObjectProperty*>(std::string("Surname"))->getValue();

//    if (surname.c_str() && firstname.c_str())
//		creo3->fullname = (std::string)firstname + " " + (std::string)surname;
//    else
//        creo3->fullname = (std::string)firstname;

	creo3->appearance = getPropertyAs<StringObjectProperty*>(std::string("Appearance"))->getValue();
	creo3->category = getPropertyAs<StringObjectProperty*>(std::string("Category"))->getValue();
	creo3->type = getPropertyAs<StringObjectProperty*>(std::string("Type"))->getValue();
	creo3->scale = getPropertyAs<FloatObjectProperty*>(std::string("Scale"))->getValue();
	creo3->posture = getPropertyAs<Uint8ObjectProperty*>(std::string("Posture"))->getValue();
	session->sendToRemote(creo3);

	std::shared_ptr<Creo6Message> creo6(GS_NEW Creo6Message());
	creo6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	creo6->mood = std::string("none");
//	creo6->hair = getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue();
	session->sendToRemote(creo6);

	std::shared_ptr<ObjPreCloseMessage> objPreClose(GS_NEW ObjPreCloseMessage());
	objPreClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objPreClose);

	std::shared_ptr<ObjCloseMessage> objClose(GS_NEW ObjCloseMessage());
	objClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objClose);

}

