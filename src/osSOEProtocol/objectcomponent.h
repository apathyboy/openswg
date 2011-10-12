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

#ifndef OPENSWG_SOEPROTOCOL_OBJECTCOMPONENT
#define OPENSWG_SOEPROTOCOL_OBJECTCOMPONENT

#include <string>
namespace osSOEProtocol
{
	class Object;
	class ObjectComponent
	{
	public:
		typedef std::string ComponentType;

		ObjectComponent() : m_owner(0) {}
		virtual ~ObjectComponent() = 0 {}

		virtual const ComponentType& getCategory() const = 0;
		virtual const ComponentType& getComponentType() const = 0;

		virtual void update() {}

		void setOwner(Object* owner) { m_owner = owner; }
		Object* getOwner() const { return m_owner; }

	private:
		Object* m_owner;
	};
}

#endif // OPENSWG_SOEPROTOCOL_OBJECTCOMPONENT

