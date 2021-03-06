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

#ifndef OPENSWG_SOEPROTOCOL_OBJECTGRID
#define OPENSWG_SOEPROTOCOL_OBJECTGRID

#include <osSOEProtocol/objectproxy.h>
#include <gsNetwork/networkmessage.h>
#include <osSOEProtocol/movementmessage.h>
#include <osSOEProtocol/cellmovementmessage.h>
#include <gsServer/session.h>

#include <boost/optional.hpp>

#include <list>

namespace osSOEProtocol
{
	class ObjectGrid
	{
	public:
		void insert(ObjectProxyPtr object);
		void update(uint64_t updateTimestamp);

		void moveObject(std::shared_ptr<osSOEProtocol::MovementMessage> movement);	
		void moveCellObject(std::shared_ptr<osSOEProtocol::CellMovementMessage> movement);	
		void sendInRange(uint64_t target, std::shared_ptr<gsNetwork::NetworkMessage> message);

		boost::optional<Object*> findObjectById(uint64_t objectId);
		boost::optional<ObjectProxyPtr> findObjectProxyById(uint64_t objectId);
		boost::optional<ObjectProxyPtr> findObjectProxyBySession(gsServer::Session* session);

		void removeObject(ObjectProxyPtr object);

	protected:
		std::list<ObjectProxyPtr> m_objects;
	};
}

#endif // OPENSWG_SOEPROTOCOL_OBJECTGRID