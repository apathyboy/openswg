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

#include <osSOEProtocol/objectgrid.h>
#include <osSOEProtocol/objectpropertytypes.h>
#include <osSOEProtocol/objdestroymessage.h>
#include <math.h>
using namespace osSOEProtocol;

boost::optional<Object*> ObjectGrid::findObjectById(uint64 objectId)
{
	boost::optional<Object*> object;
	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		if (objectId == (*i)->getObject()->getObjectId())
			return (*i)->getObject();
	}

	return object;
}

boost::optional<ObjectProxyPtr> ObjectGrid::findObjectProxyBySession(gsServer::Session* session)
{
	boost::optional<ObjectProxyPtr> object;
	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		if (session == (*i)->getSession())
			return (*i);
	}

	return object;
}

void ObjectGrid::removeObject(ObjectProxyPtr object)
{
	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		if (object->getObject()->getObjectId() == (*i)->getObject()->getObjectId())
		{
			boost::shared_ptr<ObjDestroyMessage> destroy(GS_NEW ObjDestroyMessage());
			destroy->objectId = (*i)->getObject()->getObjectId();
			object->getSession()->sendToRemote(destroy);
		
			m_objects.erase(i);

			return;
		}
	}	
}
		
boost::optional<ObjectProxyPtr> ObjectGrid::findObjectProxyById(uint64 objectId)
{
	boost::optional<ObjectProxyPtr> object;
	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		if (objectId == (*i)->getObject()->getObjectId())
			return (*i);
	}

	return object;
}

void ObjectGrid::insert(ObjectProxyPtr object)
{
	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		if (object->getObject()->getObjectId() == (*i)->getObject()->getObjectId())
			continue;		

		(*i)->addInRange(object);
	}	

	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		if (object->getObject()->getObjectId() == (*i)->getObject()->getObjectId())
			continue;		

		object->addInRange(*i);
	}	

	m_objects.push_back(object);
}

void ObjectGrid::moveCellObject(boost::shared_ptr<osSOEProtocol::CellMovementMessage> movement)
{
	boost::optional<ObjectProxyPtr> object =
		findObjectProxyById(movement->objectId);

	if (! object)
		return;

	(*object)->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(movement->cellId);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue(movement->quaternionX);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue(movement->quaternionY);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue(movement->quaternionZ);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue(movement->quaternionW);
			
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue(movement->positionX);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue(movement->positionY);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue(movement->positionZ);
	

	if (movement->quaternionX * movement->quaternionX + 
        movement->quaternionY * movement->quaternionY + 
        movement->quaternionZ * movement->quaternionZ > 0.0)
    {
	    if (movement->quaternionW > 0.0 && movement->quaternionY < 0.0)
            movement->quaternionW *= -1;

        movement->orientation = (float)(2.0*acos(movement->quaternionW));
    }
    
	else
    {
	   movement->orientation = 0.0;
    }
       
	movement->direction = (uint8)((movement->orientation/6.283)*100);	

	(*object)->getPropertyAs<Uint8ObjectProperty*>(std::string("Direction"))->setValue(movement->direction);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("Orientation"))->setValue(movement->orientation);
	movement->serialize();
	sendInRange((*object)->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue(), movement);
}

void ObjectGrid::moveObject(boost::shared_ptr<osSOEProtocol::MovementMessage> movement)
{
	boost::optional<ObjectProxyPtr> object =
		findObjectProxyById(movement->objectId);

	if (! object)
		return;

	(*object)->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(0);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionX"))->setValue(movement->quaternionX);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionY"))->setValue(movement->quaternionY);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionZ"))->setValue(movement->quaternionZ);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("QuaternionW"))->setValue(movement->quaternionW);
			
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->setValue(movement->positionX);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->setValue(movement->positionY);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->setValue(movement->positionZ);
	

	if (movement->quaternionX * movement->quaternionX + 
        movement->quaternionY * movement->quaternionY + 
        movement->quaternionZ * movement->quaternionZ > 0.0)
    {
	    if (movement->quaternionW > 0.0 && movement->quaternionY < 0.0)
            movement->quaternionW *= -1;

        movement->orientation = (float)(2.0*acos(movement->quaternionW));
    }
    
	else
    {
	   movement->orientation = 0.0;
    }
       
	movement->direction = (uint8)((movement->orientation/6.283)*100);	

	(*object)->getPropertyAs<Uint8ObjectProperty*>(std::string("Direction"))->setValue(movement->direction);
	(*object)->getPropertyAs<FloatObjectProperty*>(std::string("Orientation"))->setValue(movement->orientation);
	sendInRange((*object)->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->getValue(), movement);
}

void ObjectGrid::sendInRange(uint64 target, boost::shared_ptr<gsNetwork::NetworkMessage> message)
{
	boost::optional<ObjectProxyPtr> object = findObjectProxyById(target);
	
	if (! object)
		return;

	for (std::list<ObjectProxyPtr>::iterator i = m_objects.begin(); i != m_objects.end();++i)
	{
		//float x, y, z;

	//	x = (*i)->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue() -
	//		(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionX"))->getValue();
	//	y = (*i)->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue() -
	//		(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionY"))->getValue();
	//	z = (*i)->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue() -
	//		(*object)->getPropertyAs<FloatObjectProperty*>(std::string("PositionZ"))->getValue();

		//if (! (sqrt((x * x) + (y * y) + (z * z)) <= 512))
		//	continue;

		if ((*i)->hasSession())
		{
			boost::shared_ptr<gsNetwork::NetworkMessage> clone =
				message->clone();

			clone->recipientId = (*i)->getObject()->getObjectId();		
			(*i)->getSession()->sendToRemote(clone);
		}
	}
}


void ObjectGrid::update(uint64 updateTimestamp)
{
	// Move objects to new cells.
}