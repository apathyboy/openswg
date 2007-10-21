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

#ifndef OPENSWG_SOEPROTOCOL_TANGIBLEOBJECT
#define OPENSWG_SOEPROTOCOL_TANGIBLEOBJECT

#include <osSOEProtocol/export.h>
#include <boost/shared_ptr.hpp>
#include <osSOEProtocol/object.h>
namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT TangibleObject : public Object
	{
	public:
		TangibleObject() {}
		virtual ~TangibleObject(){}

		void setCustomName(std::string customName) { m_customName = customName; }
		std::string getCustomName() { return m_customName; }

		void setColor(std::string color) { m_color = color; }
		std::string getColor() { return m_color; }

		void setEquipped(bool equipped) { m_equipped = equipped; }
		bool getEquipped() { return m_equipped; }

	private:
		std::string m_customName;
		std::string m_color;
		bool m_equipped;
	};

	typedef OS_SOEPROTOCOL_EXPORT boost::shared_ptr<TangibleObject> TangibleObjectPtr;
}

#endif // OPENSWG_SOEPROTOCOL_TANGIBLEOBJECT