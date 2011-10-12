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

#ifndef OPENSWG_SOEPROTOCOL_CREO3MESSAGE
#define OPENSWG_SOEPROTOCOL_CREO3MESSAGE

#include <gsNetwork/binarypacket.h>
#include <gsNetwork/networkmessage.h>

namespace osSOEProtocol
{
	class Creo3Message : public gsNetwork::NetworkMessage
	{
	public:
		uint32_t healthWounds;
		uint32_t strengthWounds;
		uint32_t constitutionWounds;
		uint32_t actionWounds;
		uint32_t quicknessWounds;
		uint32_t staminaWounds;
		uint32_t mindWounds;
		uint32_t focusWounds;
		uint32_t willpowerWounds;

		uint64_t objectId;
		uint64_t targetId;
		uint32_t battleFatigue;
		std::string fullname;
		std::string category;
		std::string type;
		std::string appearance;
		float scale;
		uint8_t posture;

		Creo3Message();
		Creo3Message(gsNetwork::BinaryPacketPtr packet);
		virtual ~Creo3Message();

		virtual gsNetwork::BinaryPacketPtr serialize();
		virtual void unserialize();
	};
}

#endif // OPENSWG_SOEPROTOCOL_CREO3MESSAGE