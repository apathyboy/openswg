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

#ifndef OPENSWG_SOEPROTOCOL_TANGIBLEOBJECTPROXY
#define OPENSWG_SOEPROTOCOL_TANGIBLEOBJECTPROXY

#include <osSOEProtocol/export.h>
#include <osSOEProtocol/objectproxy.h>
#include <osSOEProtocol/tangibleobject.h>


namespace gsServer
{
	class Session;
}

namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT TangibleObjectProxy : public ObjectProxy
	{
	public:
		TangibleObjectProxy();
		void createTemplate();
		virtual void loadFromDatabaseId(uint64 objectId);
		virtual void addInRange(boost::shared_ptr<ObjectProxy> object){};
		virtual void sendInRange(gsNetwork::NetworkMessagePtr message){};
		virtual void sendReliableUpdate(gsServer::Session* session);

		virtual void update(uint64 updateTimestamp) {}
		virtual void buildPropertyMap();

		virtual void createFromTemplate(std::string templateItem);
		virtual void store();
		virtual void setLinkType(uint linkType) { m_linkType = linkType; }
		virtual uint getLinkType() { return m_linkType; }

	protected:
		uint m_linkType;
		virtual void createObject();
	};

	typedef OS_SOEPROTOCOL_EXPORT boost::shared_ptr<TangibleObjectProxy> TangibleObjectProxyPtr;
}

#endif // OPENSWG_SOEPROTOCOL_TANGIBLEOBJECTPROXY

