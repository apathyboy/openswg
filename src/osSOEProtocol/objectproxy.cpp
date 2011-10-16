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
	std::shared_ptr<MovementMessage> message(new MovementMessage);

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
        std::bind(&Object::setDatabaseId, m_object, std::placeholders::_1), 
        std::bind(&Object::getDatabaseId, m_object),
		"A local database table id.", 
		GROUPNAME));

	addProperty(new Uint64ObjectProperty(
		"ObjectId", "Object ID", 
        std::bind(&Object::setObjectId, m_object, std::placeholders::_1), 
        std::bind(&Object::getObjectId, m_object),
		"A globally unique identifier assigned to every object.", 
		GROUPNAME));

	addProperty(new Uint64ObjectProperty(
		"ParentId", "Parent ID", 
        std::bind(&Object::setParentId, m_object, std::placeholders::_1), 
        std::bind(&Object::getParentId, m_object), 
		"A globally unique identifier assigned to every object.", 
		GROUPNAME));

	addProperty(new Uint64ObjectProperty(
		"ZoneId", "Zone ID", 
        std::bind(&Object::setZoneId, m_object, std::placeholders::_1), 
        std::bind(&Object::getZoneId, m_object),
		"Zone ID of the current object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Model", "Model", 
        std::bind(&Object::setModel, m_object, std::placeholders::_1), 
        std::bind(&Object::getModel, m_object),
		"Model string for the object.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Category", "Category", 
        std::bind(&Object::setCategory, m_object, std::placeholders::_1), 
        std::bind(&Object::getCategory, m_object),
		"Category of the object model.", 
		GROUPNAME));
	
	addProperty(new StringObjectProperty(
		"Type", "Type", 
        std::bind(&Object::setType, m_object, std::placeholders::_1), 
        std::bind(&Object::getType, m_object),
		"Type of the object model.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionX", "Quaternion X", 
        std::bind(&Object::setQuaternionX, m_object, std::placeholders::_1), 
        std::bind(&Object::getQuaternionX, m_object),
		"Quaternion X.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionY", "Quaternion Y", 
        std::bind(&Object::setQuaternionY, m_object, std::placeholders::_1), 
        std::bind(&Object::getQuaternionY, m_object),
		"Quaternion Y.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionZ", "Quaternion Z", 
        std::bind(&Object::setQuaternionZ, m_object, std::placeholders::_1), 
        std::bind(&Object::getQuaternionZ, m_object),
		"Quaternion X.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"QuaternionW", "QuaternionW", 
        std::bind(&Object::setQuaternionW, m_object, std::placeholders::_1), 
        std::bind(&Object::getQuaternionW, m_object),
		"Quaternion W.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"PositionX", "Position X", 
        std::bind(&Object::setPositionX, m_object, std::placeholders::_1), 
        std::bind(&Object::getPositionX, m_object),
		"Position X.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"PositionY", "Position Y", 
        std::bind(&Object::setPositionY, m_object, std::placeholders::_1), 
        std::bind(&Object::getPositionY, m_object),
		"Position Y.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"PositionZ", "Position Z", 
        std::bind(&Object::setPositionZ, m_object, std::placeholders::_1), 
        std::bind(&Object::getPositionZ, m_object),
		"Position Z.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"Scale", "Scale", 
        std::bind(&Object::setScale, m_object, std::placeholders::_1), 
        std::bind(&Object::getScale, m_object),
		"Scale of the object.", 
		GROUPNAME));
	
	addProperty(new FloatObjectProperty(
		"Orientation", "Orientation", 
        std::bind(&Object::setOrientation, m_object, std::placeholders::_1), 
        std::bind(&Object::getOrientation, m_object),
		"Orientation of the object.", 
		GROUPNAME));
	
	addProperty(new Uint8ObjectProperty(
		"Direction", "Direction", 
        std::bind(&Object::setDirection, m_object, std::placeholders::_1), 
        std::bind(&Object::getDirection, m_object),
		"Directional facing of the object.", 
		GROUPNAME));

	addProperty(new UintObjectProperty(
		"State", "State", 
        std::bind(&Object::setState, m_object, std::placeholders::_1), 
        std::bind(&Object::getState, m_object),
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

