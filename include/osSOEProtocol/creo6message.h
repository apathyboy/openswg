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

#ifndef OPENSWG_SOEPROTOCOL_CREO6MESSAGE
#define OPENSWG_SOEPROTOCOL_CREO6MESSAGE

#include <gsNetwork/binarypacket.h>
#include <gsNetwork/networkmessage.h>
#include <osSOEProtocol/export.h>

namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT Creo6Message : public gsNetwork::NetworkMessage
	{
	public:
		uint32 maxHealth;
		uint32 currentHealth;
		uint32 maxStrength;
		uint32 currentStrength;
		uint32 maxConstitution;
		uint32 currentConstitution;
		uint32 maxAction;
		uint32 currentAction;
		uint32 maxQuickness;
		uint32 currentQuickness;
		uint32 maxStamina;
		uint32 currentStamina;
		uint32 maxMind;
		uint32 currentMind;
		uint32 maxFocus;
		uint32 currentFocus;
		uint32 maxWillpower;
		uint32 currentWillpower;

		uint64 objectId;
		std::string mood;
		std::string hair;
		bool isPlayer;

		Creo6Message();
		Creo6Message(gsNetwork::BinaryPacketPtr packet);
		virtual ~Creo6Message();

		virtual gsNetwork::BinaryPacketPtr serialize();
		virtual void unserialize();
	};
}

#endif // OPENSWG_SOEPROTOCOL_CREO6MESSAGE