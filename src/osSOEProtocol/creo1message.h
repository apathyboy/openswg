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

#ifndef OPENSWG_SOEPROTOCOL_CREO1MESSAGE
#define OPENSWG_SOEPROTOCOL_CREO1MESSAGE

#include <gsNetwork/binarypacket.h>
#include <gsNetwork/networkmessage.h>

namespace osSOEProtocol
{
	class Creo1Message : public gsNetwork::NetworkMessage
	{
	public:
		uint32_t healthModifiers;
		uint32_t strengthModifiers;
		uint32_t constitutionModifiers;
		uint32_t actionModifiers;
		uint32_t quicknessModifiers;
		uint32_t staminaModifiers;
		uint32_t mindModifiers;
		uint32_t focusModifiers;
		uint32_t willpowerModifiers;

		uint64_t objectId;
		uint32_t bankCredits;
		uint32_t inventoryCredits;

		Creo1Message();
		Creo1Message(gsNetwork::BinaryPacketPtr packet);
		virtual ~Creo1Message();

		virtual gsNetwork::BinaryPacketPtr serialize();
		virtual void unserialize();
	};
}

#endif // OPENSWG_SOEPROTOCOL_CREO1MESSAGE

