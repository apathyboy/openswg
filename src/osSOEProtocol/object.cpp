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

#include <osSOEProtocol/object.h>

using namespace osSOEProtocol;

boost::optional<ObjectComponent*> Object::getComponent(const ObjectComponent::ComponentType& category)
{
	boost::optional<ObjectComponent*> component;

	ComponentTable::iterator i = m_components.find((*component)->getCategory());

	if (i != m_components.end())
	{
		component = (*i).second;
	}

	return component;
}

boost::optional<ObjectComponent*> Object::setComponent(ObjectComponent* component)
{
	boost::optional<ObjectComponent*> currentComponent;

	ComponentTable::iterator i = m_components.find(component->getCategory());

	if (i != m_components.end())
	{
		currentComponent = (*i).second;
		(*i).second = component;
	}
	else
	{
		std::pair<const ObjectComponent::ComponentType, ObjectComponent*> insert =
			std::make_pair<const ObjectComponent::ComponentType, ObjectComponent*>(component->getCategory(), component);

		m_components.insert(insert);
	}

	return currentComponent;
}

void Object::clearComponents()
{
	m_components.clear();
}

