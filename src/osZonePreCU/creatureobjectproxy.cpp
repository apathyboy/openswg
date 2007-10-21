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

#include <osZonePreCU/creatureobject.h>
#include <osZonePreCU/creatureobjectproxy.h>
#include <osZonePreCU/objectpropertytypes.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;

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
		makeFunctor((CBFunctor1<uint8>*)0, *creature, &CreatureObject::setPosture), 
		makeFunctor((CBFunctor0wRet<uint8>*)0, *creature, &CreatureObject::getPosture), 
		"Posture of the creature object.", 
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