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

#ifndef OPENSWG_ZONEPRECU_CREATUREOBJECT
#define OPENSWG_ZONEPRECU_CREATUREOBJECT

#include <boost/shared_ptr.hpp>
#include <osZonePreCU/object.h>
namespace osZonePreCU
{
	class CreatureObject : public Object
	{
	public:
		CreatureObject() {m_posture = 0;}
		virtual ~CreatureObject(){}

		std::string getAppearance() { return m_appearance; }
		void setAppearance(std::string appearance) { m_appearance = appearance; }
		
		std::string getPlanet() { return m_planet; }
		void setPlanet(std::string planet) { m_planet = planet; }
		
		std::string getMood() { return m_mood; }
		void setMood(std::string mood) { m_mood = mood; }
		
		uint8 getPosture() { return m_posture; }
		void setPosture(uint8 posture) { m_posture = posture; }

	private:
		std::string m_appearance;
		std::string m_planet;
		std::string m_mood;
		uint8 m_posture;
	};

	typedef boost::shared_ptr<CreatureObject> CreatureObjectPtr;
}

#endif // OPENSWG_ZONEPRECU_CREATUREOBJECT