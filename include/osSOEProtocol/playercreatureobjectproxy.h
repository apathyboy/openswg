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

#ifndef OPENSWG_SOEPROTOCOL_PLAYERCREATUREOBJECTPROXY
#define OPENSWG_SOEPROTOCOL_PLAYERCREATUREOBJECTPROXY

#include <osSOEProtocol/export.h>
#include <osSOEProtocol/creatureobjectproxy.h>
#include <osSOEProtocol/tangibleobjectproxy.h>

namespace gsServer
{
	class Session;
}

namespace osSOEProtocol
{		
	class OS_SOEPROTOCOL_EXPORT PlayerCreatureObjectProxy : public CreatureObjectProxy
	{
	public:
		PlayerCreatureObjectProxy();
		virtual void loadFromDatabaseId(uint64 databaseId);
		virtual void setPlayerSession(gsServer::Session* session);
		virtual void buildPropertyMap();
		virtual void update(uint64 updateTimestamp);
		virtual void store();

		void loadItems();

		virtual void addInRange(boost::shared_ptr<ObjectProxy> object);
		virtual void sendReliableUpdate(gsServer::Session* session);
		virtual void sendInRange(gsNetwork::NetworkMessagePtr message);
	public:
		
	protected:
		virtual void createObject();

		std::vector<boost::shared_ptr<TangibleObjectProxy> > m_items;
	};

	typedef OS_SOEPROTOCOL_EXPORT boost::shared_ptr<PlayerCreatureObjectProxy> PlayerCreatureObjectProxyPtr;
}

#endif // OPENSWG_SOEPROTOCOL_PLAYERCREATUREOBJECTPROXY

