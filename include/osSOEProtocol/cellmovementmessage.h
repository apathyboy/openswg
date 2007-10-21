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

#ifndef OPENSWG_SOEPROTOCOL_CELLMOVEMENTMESSAGE
#define OPENSWG_SOEPROTOCOL_CELLMOVEMENTMESSAGE

#include <gsNetwork/binarypacket.h>
#include <gsNetwork/networkmessage.h>
#include <osSOEProtocol/export.h>
#include <osSOEProtocol/movementmessage.h>

namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT CellMovementMessage : public gsNetwork::NetworkMessage
	{
	public:
		uint64 objectId; // Target (this is the character moving)
        uint32 ticks; // Ticks?
        uint32 timer; // Times?
        uint8 direction;
        uint64 cellId;
        float quaternionX; // Orientation x
        float quaternionY; // Orientation y
        float quaternionZ; // Orientation z
        float quaternionW; // Orientation w
        float positionX; // position x
        float positionY; // position y
        float positionZ; // position z
        float speed; // speed
		float orientation;

		bool movedX;
		bool movedY;
		bool movedZ;

		CellMovementMessage();
		CellMovementMessage(gsNetwork::BinaryPacketPtr packet);
		virtual ~CellMovementMessage();

		virtual boost::shared_ptr<NetworkMessage> clone();

		virtual gsNetwork::BinaryPacketPtr serialize();
		virtual void unserialize();
	};
}

#endif // OPENSWG_SOEPROTOCOL_CELLMOVEMENTMESSAGE