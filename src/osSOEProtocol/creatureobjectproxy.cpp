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
	boost::shared_ptr<CreatureObject> creature(GS_NEW CreatureObject);
	m_object = creature;

	buildPropertyMap();
}

void CreatureObjectProxy::buildPropertyMap()
{
	ObjectProxy::buildPropertyMap();

    const std::string GROUPNAME = "Creature";

	boost::shared_ptr<CreatureObject> creature = boost::shared_dynamic_cast<CreatureObject>(m_object);

	addProperty(new StringObjectProperty(
		"Appearance", "Appearance", 
		makeFunctor((CBFunctor1<std::string>*)0, *creature, &CreatureObject::setAppearance), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *creature, &CreatureObject::getAppearance), 
		"Appearance string of the creature object. Note that in the future this will be expanded to include modification of the individual items of the appearance string.", 
		GROUPNAME));
	
	addProperty(new Uint8ObjectProperty(
		"Posture", "Posture", 
		makeFunctor((CBFunctor1<uint8_t>*)0, *creature, &CreatureObject::setPosture), 
		makeFunctor((CBFunctor0wRet<uint8_t>*)0, *creature, &CreatureObject::getPosture), 
		"Posture of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint64ObjectProperty(
		"TargetId", "Target Id", 
		makeFunctor((CBFunctor1<uint64_t>*)0, *creature, &CreatureObject::setTargetId), 
		makeFunctor((CBFunctor0wRet<uint64_t>*)0, *creature, &CreatureObject::getTargetId), 
		"Target id of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxHealth", "Max Health", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxHealth), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxHealth), 
		"Max health of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxStrength", "Max Strength", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxStrength), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxStrength), 
		"Max strength of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxConstitution", "Max Constitution", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxConstitution), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxConstitution), 
		"Max constitution of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxAction", "Max Action", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxAction), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxAction), 
		"Max action of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxQuickness", "Max Quickness", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxQuickness), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxQuickness), 
		"Max quickness of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxStamina", "Max Stamina", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxStamina), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxStamina), 
		"Max stamina of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxMind", "Max Mind", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxMind), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxMind), 
		"Max mind of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxFocus", "Max Focus", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxFocus), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxFocus), 
		"Max focus of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MaxWillpower", "Max Willpower", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMaxWillpower), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMaxWillpower), 
		"Max willpower of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentHealth", "Current Health", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentHealth), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentHealth), 
		"Current health of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentStrength", "Current Strength", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentStrength), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentStrength), 
		"Current strength of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentConstitution", "Current Constitution", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentConstitution), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentConstitution), 
		"Current constitution of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentAction", "Current Action", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentAction), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentAction), 
		"Current action of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentQuickness", "Current Quickness", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentQuickness), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentQuickness), 
		"Current quickness of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentStamina", "Current Stamina", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentStamina), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentStamina), 
		"Current stamina of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentMind", "Current Mind", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentMind), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentMind), 
		"Current mind of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentFocus", "Current Focus", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentFocus), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentFocus), 
		"Max focus of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CurrentWillpower", "Current Willpower", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCurrentWillpower), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCurrentWillpower), 
		"Current willpower of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"HealthWounds", "HealthWounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setHealthWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getHealthWounds), 
		"Health wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StrengthWounds", "StrengthWounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setStrengthWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getStrengthWounds), 
		"Strength wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ConstitutionWounds", "Constitution Wounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setConstitutionWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getConstitutionWounds), 
		"Constitution wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ActionWounds", "Action Wounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setActionWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getActionWounds), 
		"Action wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"QuicknessWounds", "QuicknessWounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setQuicknessWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getQuicknessWounds), 
		"Quickness wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StaminaWounds", "Stamina Wounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setStaminaWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getStaminaWounds), 
		"Stamina wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MindWounds", "MindWounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMindWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMindWounds), 
		"Mind wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"FocusWounds", "Focus Wounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setFocusWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getFocusWounds), 
		"Focus wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"WillpowerWounds", "Willpower Wounds", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setWillpowerWounds), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getWillpowerWounds), 
		"Willpower wounds of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"HealthModifiers", "Health Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setHealthModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getHealthModifiers), 
		"Health modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StrengthModifiers", "Strength Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setStrengthModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getStrengthModifiers), 
		"Strength modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ConstitutionModifiers", "Constitution Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setConstitutionModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getConstitutionModifiers), 
		"Constitution modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"ActionModifiers", "Action modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setActionModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getActionModifiers), 
		"Action modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"QuicknessModifiers", "Quickness Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setQuicknessModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getQuicknessModifiers), 
		"Quickness modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"StaminaModifiers", "Stamina Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setStaminaModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getStaminaModifiers), 
		"Stamina modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"MindModifiers", "Mind Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setMindModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getMindModifiers), 
		"Mind modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"FocusModifiers", "Focus Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setFocusModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getFocusModifiers), 
		"Focus modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"WillpowerModifiers", "Willpower Modifiers", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setWillpowerModifiers), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getWillpowerModifiers), 
		"Willpower modifiers of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"CreatureType", "Creature Type", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setCreatureType), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getCreatureType), 
		"Creature type of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"FactionAlignment", "Faction Alignment", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setFactionAlignment), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getFactionAlignment), 
		"Faction alignment of the creature object.", 
		GROUPNAME));
	
	addProperty(new Uint32ObjectProperty(
		"BattleFatigue", "Battle Fatigue", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *creature, &CreatureObject::setBattleFatigue), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *creature, &CreatureObject::getBattleFatigue), 
		"Battle fatigue of the creature object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Mood", "Mood", 
		makeFunctor((CBFunctor1<std::string>*)0, *creature, &CreatureObject::setMood), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *creature, &CreatureObject::getMood), 
		"Mood of the creature object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Planet", "Planet", 
		makeFunctor((CBFunctor1<std::string>*)0, *creature, &CreatureObject::setPlanet), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *creature, &CreatureObject::getPlanet), 
		"Planet where the creature is currently located.", 
		GROUPNAME));
}

void CreatureObjectProxy::sendReliableUpdate(Session* session)
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

	boost::shared_ptr<Creo3Message> creo3(GS_NEW Creo3Message());
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

	boost::shared_ptr<Creo6Message> creo6(GS_NEW Creo6Message());
	creo6->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	creo6->mood = std::string("none");
//	creo6->hair = getPropertyAs<StringObjectProperty*>(std::string("Hair"))->getValue();
	session->sendToRemote(creo6);

	boost::shared_ptr<ObjPreCloseMessage> objPreClose(GS_NEW ObjPreCloseMessage());
	objPreClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objPreClose);

	boost::shared_ptr<ObjCloseMessage> objClose(GS_NEW ObjCloseMessage());
	objClose->objectId = getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue();
	session->sendToRemote(objClose);

}

