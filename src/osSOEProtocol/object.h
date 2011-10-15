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

#ifndef OPENSWG_SOEPROTOCOL_OBJECT
#define OPENSWG_SOEPROTOCOL_OBJECT

#include <cstdint>

#include <osSOEProtocol/objectcomponent.h>
#include <osSOEProtocol/objectcomponenttemplate.h>

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <map>

namespace osSOEProtocol
{
	typedef std::string ObjectType;
	class Object
	{
		
	public: // Object Type

		const ObjectType& getObjectType() const { return m_classType; }
		void setObjectType(ObjectType type) { m_classType = type; }

	protected:
		ObjectType m_classType;

	public: // Object Components
		boost::optional<ObjectComponent*> getComponent(const ObjectComponent::ComponentType& category);
		boost::optional<ObjectComponent*> setComponent(ObjectComponent* component);
		void clearComponents();

	protected:
		typedef std::map<const ObjectComponent::ComponentType, ObjectComponent*> ComponentTable;
		
		ComponentTable m_components;

	public:
		Object()
		: m_qx(0)
		, m_qy(0)
		, m_qz(0)
		, m_qw(0)
		, m_px(0)
		, m_py(0)
		, m_pz(0)
		{}
		virtual ~Object(){}

		void setDatabaseId(uint64_t id) { m_databaseId = id; }
		uint64_t getDatabaseId() { return m_databaseId; }

		void setParentId(uint64_t parentId) { m_parentId = parentId; }
		uint64_t getParentId() { return m_parentId; }

		void setObjectId(uint64_t id) { m_id = id; }
		uint64_t getObjectId() { return m_id; }

		void setZoneId(uint64_t zoneId) { m_zoneId = zoneId; }
		uint64_t getZoneId() { return m_zoneId; }

		void setModel(std::string model) { m_model = model; }
		std::string getModel() { return m_model; }

		void setCategory(std::string category) { m_category = category; }
		std::string getCategory() { return m_category; }

		void setType(std::string type) { m_type = type; }
		std::string getType() { return m_type; }

		void setQuaternionX(float qx) { m_qx = qx; }
		float getQuaternionX() { return m_qx; }

		void setQuaternionY(float qy) { m_qy = qy; }
		float getQuaternionY() { return m_qy; }

		void setQuaternionZ(float qz) { m_qz = qz; }
		float getQuaternionZ() { return m_qz; }

		void setQuaternionW(float qw) { m_qw = qw; }
		float getQuaternionW() { return m_qw; }

		void setPositionX(float px) { m_px = px; }
		float getPositionX() { return m_px; }

		void setPositionY(float py) { m_py = py; }
		float getPositionY() { return m_py; }

		void setPositionZ(float pz) { m_pz = pz; }
		float getPositionZ() { return m_pz; }

		void setScale(float scale) { m_scale = scale; }
		float getScale() { return m_scale; }

		void setOrientation(float orientation) { m_orientation = orientation; }
		float getOrientation() { return m_orientation; }

		void setDirection(uint8_t direction) { m_direction = direction; }
		uint8_t getDirection() { return m_direction; }

		void setState(uint32_t state) { m_state = state; }
		uint32_t getState() { return m_state; }
	private:
		uint64_t m_id;	
		uint64_t m_databaseId;	
		uint64_t m_zoneId;
		uint64_t m_parentId;
		std::string m_model;
		std::string m_category;
		std::string m_type;
		float m_qx;
		float m_qy;
		float m_qz;
		float m_qw;
		float m_px;
		float m_py;
		float m_pz;
		float m_scale;
		float m_orientation;
		uint8_t m_direction;
		uint32_t m_state;
	};

	typedef std::shared_ptr<Object> ObjectPtr;
}

#endif // OPENSWG_SOEPROTOCOL_OBJECT