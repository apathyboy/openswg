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

#ifndef OPENSWG_SOEPROTOCOL_OBJECTPROXY
#define OPENSWG_SOEPROTOCOL_OBJECTPROXY

#include <gsServer/session.h>

#include <osSOEProtocol/object.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>

namespace osSOEProtocol
{
	class Object;
	class ObjectProperty;
	class ObjectProxy
	{
	public:
		ObjectProxy();

		virtual Object* getObject();
		virtual void loadFromDatabaseId(uint64_t objectId) = 0;
		virtual void update(uint64_t updateTimestamp) {}

		bool hasSession() { return (m_session != NULL) ? true : false; }
		gsServer::Session* getSession() { return m_session; }

		virtual void addInRange(boost::shared_ptr<ObjectProxy> object) =0;
		virtual void sendReliableUpdate(gsServer::Session* session) = 0;
		virtual void sendInRange(gsNetwork::NetworkMessagePtr message) = 0;
		virtual void notifyInRange(bool sendToSelf);
		virtual void sendMovementUpdate(gsServer::Session* session);
		virtual void store() {}

	public: // Radial System Methods
		virtual void radialSelection(uint8_t option, gsServer::Session* session);
		

	public: // ObjectProperty
		void addProperty(ObjectProperty* newProperty);
		void removeProperty(const std::string& name);
		ObjectProperty* getProperty(const std::string& name);

		bool hasMoved() { return m_hasMoved; }
		void setMoved(bool moved) { m_hasMoved = moved; }

		virtual void buildPropertyMap();
		
		template <typename T>
        T getPropertyAs(const std::string& name)
        {
			ObjectProperty* property = getProperty(name);
			return dynamic_cast<T>(property);
        }

		bool checkPropertiesBuilt() { return m_propertiesBuilt; }
		void setPropertiesBuilt(bool built) { m_propertiesBuilt = built; }

	protected:
		virtual void createObject() = 0;
		uint64_t m_objectId;
		ObjectPtr m_object;

		gsServer::Session* m_session;

		std::vector<boost::shared_ptr<ObjectProxy> > m_inRange;
	private:
		bool m_hasMoved;
		bool m_propertiesBuilt;


         ///Map of properties.
         std::map<std::string, boost::shared_ptr<ObjectProperty> > m_propertyMap;

         ///vector of properties (for order).
		 std::vector<boost::shared_ptr<ObjectProperty> > m_properties;
	};

	typedef boost::shared_ptr<ObjectProxy> ObjectProxyPtr;
}

#endif // OPENSWG_SOEPROTOCOL_OBJECTPROXY

