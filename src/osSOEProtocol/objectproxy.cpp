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

#include "osSOEProtocol/objectproxy.h"

#ifdef ERROR
#undef ERROR
#endif
#include <glog/logging.h>

#include <osSOEProtocol/object.h>


#include <osSOEProtocol/objectproperty.h>
#include <osSOEProtocol/objectpropertytypes.h>
#include <osSOEProtocol/movementmessage.h>

using namespace gsCore;
using namespace osSOEProtocol;

ObjectProxy::ObjectProxy()
: m_objectId(0)
{
	m_session = NULL;
	m_propertiesBuilt = false;
}

Object* ObjectProxy::getObject()
{
	return m_object.get();
}

void ObjectProxy::notifyInRange(bool sendToSelf)
{
	if(sendToSelf)
		sendReliableUpdate(m_session);

	for (std::vector<std::shared_ptr<ObjectProxy> >::iterator itor = m_inRange.begin();
		itor != m_inRange.end(); ++itor)
	{
		if ((*itor)->hasSession())
		{	
			printf("Notifying in range\n");
			sendReliableUpdate((*itor)->getSession());
		}
	}
}

void ObjectProxy::radialSelection(uint8_t option, gsServer::Session* session)
{
}
		
void ObjectProxy::sendMovementUpdate(gsServer::Session* session)
{
	std::shared_ptr<MovementMessage> message(GS_NEW MovementMessage);

	message->objectId; // Target (this is the character moving)
    message->ticks; // Ticks?
    message->timer; // Times?
    message->direction;
    message->quaternionX; // Orientation x
    message->quaternionY; // Orientation y
    message->quaternionZ; // Orientation z
    message->quaternionW; // Orientation w
    message->positionX; // position x
    message->positionY; // position y
    message->positionZ; // position z

	session->sendToRemote(message);
	
}

void ObjectProxy::addInRange(std::shared_ptr<ObjectProxy> object)
{
	std::vector<std::shared_ptr<ObjectProxy> >::iterator itor = 
		m_inRange.begin();

	for (; itor != m_inRange.end(); ++itor)
	{
		if ((*itor) == object)
			return;
	}
	
	m_inRange.push_back(object);
}

void ObjectProxy::buildPropertyMap()
{
	if (! m_object)
		return;

    const std::string GROUPNAME = "Object";

	addProperty(new Uint64ObjectProperty(
		"DatabaseId", "Database ID", 
		makeFunctor((CBFunctor1<uint64_t>*)0, *m_object, &Object::setDatabaseId), 
		makeFunctor((CBFunctor0wRet<uint64_t>*)0, *m_object, &Object::getDatabaseId), 
		"A local database table id.", 
		GROUPNAME));

	addProperty(new Uint64ObjectProperty(
		"ObjectId", "Object ID", 
		makeFunctor((CBFunctor1<uint64_t>*)0, *m_object, &Object::setObjectId), 
		makeFunctor((CBFunctor0wRet<uint64_t>*)0, *m_object, &Object::getObjectId), 
		"A globally unique identifier assigned to every object.", 
		GROUPNAME));

	addProperty(new Uint64ObjectProperty(
		"ParentId", "Parent ID", 
		makeFunctor((CBFunctor1<uint64_t>*)0, *m_object, &Object::setParentId), 
		makeFunctor((CBFunctor0wRet<uint64_t>*)0, *m_object, &Object::getParentId), 
		"A globally unique identifier assigned to every object.", 
		GROUPNAME));

	addProperty(new Uint64ObjectProperty(
		"ZoneId", "Zone ID", 
		makeFunctor((CBFunctor1<uint64_t>*)0, *m_object, &Object::setZoneId), 
		makeFunctor((CBFunctor0wRet<uint64_t>*)0, *m_object, &Object::getZoneId), 
		"Zone ID of the current object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Model", "Model", 
		makeFunctor((CBFunctor1<std::string>*)0, *m_object, &Object::setModel), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *m_object, &Object::getModel), 
		"Model string for the object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Category", "Category", 
		makeFunctor((CBFunctor1<std::string>*)0, *m_object, &Object::setCategory), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *m_object, &Object::getCategory), 
		"Category of the object model.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Type", "Type", 
		makeFunctor((CBFunctor1<std::string>*)0, *m_object, &Object::setType), 
		makeFunctor((CBFunctor0wRet<std::string>*)0, *m_object, &Object::getType), 
		"Type of the object model.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionX", "Quaternion X", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setQuaternionX), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getQuaternionX), 
		"Quaternion X.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionY", "Quaternion Y", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setQuaternionY), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getQuaternionY), 
		"Quaternion Y.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionZ", "Quaternion Z", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setQuaternionZ), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getQuaternionZ), 
		"Quaternion X.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionW", "QuaternionW", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setQuaternionW), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getQuaternionW), 
		"Quaternion W.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"PositionX", "Position X", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setPositionX), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getPositionX), 
		"Position X.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"PositionY", "Position Y", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setPositionY), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getPositionY), 
		"Position Y.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"PositionZ", "Position Z", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setPositionZ), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getPositionZ), 
		"Position Z.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"Scale", "Scale", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setScale), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getScale), 
		"Scale of the object.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"Orientation", "Orientation", 
		makeFunctor((CBFunctor1<float>*)0, *m_object, &Object::setOrientation), 
		makeFunctor((CBFunctor0wRet<float>*)0, *m_object, &Object::getOrientation), 
		"Orientation of the object.", 
		GROUPNAME));
	
	addProperty(new Uint8ObjectProperty(
		"Direction", "Direction", 
		makeFunctor((CBFunctor1<uint8_t>*)0, *m_object, &Object::setDirection), 
		makeFunctor((CBFunctor0wRet<uint8_t>*)0, *m_object, &Object::getDirection), 
		"Directional facing of the object.", 
		GROUPNAME));

	addProperty(new UintObjectProperty(
		"State", "State", 
		makeFunctor((CBFunctor1<uint32_t>*)0, *m_object, &Object::setState), 
		makeFunctor((CBFunctor0wRet<uint32_t>*)0, *m_object, &Object::getState), 
		"State.", 
		GROUPNAME));
}

void ObjectProxy::addProperty(ObjectProperty* newProperty)
{
	if (newProperty == NULL)
	{
		// Throw exception here.
	}

	std::map<std::string, std::shared_ptr<ObjectProperty> >::iterator itor =
		m_propertyMap.find(newProperty->getName());
	if (itor != m_propertyMap.end())
	{
        LOG(ERROR) << "Property already exists: " << newProperty->getName();
	}
	else
	{
		std::shared_ptr<ObjectProperty> propertyPtr(newProperty);
		m_propertyMap.insert(std::make_pair(newProperty->getName(), propertyPtr));
		m_properties.push_back(propertyPtr);
	}
}
		
void ObjectProxy::removeProperty(const std::string& name)
{
	std::map<std::string, std::shared_ptr<ObjectProperty> >::iterator itor =
		m_propertyMap.find(name);
	if (itor != m_propertyMap.end())
	{
		m_propertyMap.erase(itor);
		for (uint32_t i = 0; i < m_properties.size(); ++i)
		{
			if (m_properties[i]->getName() == name)
			{
				m_properties.erase(m_properties.begin() + i);
				break;
			}
		}
	}
	else
	{
        LOG(ERROR) << "Property does not exist: " << name;
	}
}
		
ObjectProperty* ObjectProxy::getProperty(const std::string& name)
{
	std::map<std::string, std::shared_ptr<ObjectProperty> >::iterator itor =
		m_propertyMap.find(name);
	
	if (itor == m_propertyMap.end())
		return NULL;
	else
		return itor->second.get();
}

