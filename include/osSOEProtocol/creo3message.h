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
#include <osSOEProtocol/export.h>

namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT Creo3Message : public gsNetwork::NetworkMessage
	{
	public:
		uint32 healthWounds;
		uint32 strengthWounds;
		uint32 constitutionWounds;
		uint32 actionWounds;
		uint32 quicknessWounds;
		uint32 staminaWounds;
		uint32 mindWounds;
		uint32 focusWounds;
		uint32 willpowerWounds;

		uint64 objectId;
		uint64 targetId;
		uint32 battleFatigue;
		std::string fullname;
		std::string category;
		std::string type;
		std::string appearance;
		float scale;
		uint8 posture;

		Creo3Message();
		Creo3Message(gsNetwork::BinaryPacketPtr packet);
		virtual ~Creo3Message();

		virtual gsNetwork::BinaryPacketPtr serialize();
		virtual void unserialize();
	};
}

#endif // OPENSWG_SOEPROTOCOL_CREO3MESSAGE