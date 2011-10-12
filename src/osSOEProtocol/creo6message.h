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

namespace osSOEProtocol
{
	class Creo6Message : public gsNetwork::NetworkMessage
	{
	public:
		uint32_t maxHealth;
		uint32_t currentHealth;
		uint32_t maxStrength;
		uint32_t currentStrength;
		uint32_t maxConstitution;
		uint32_t currentConstitution;
		uint32_t maxAction;
		uint32_t currentAction;
		uint32_t maxQuickness;
		uint32_t currentQuickness;
		uint32_t maxStamina;
		uint32_t currentStamina;
		uint32_t maxMind;
		uint32_t currentMind;
		uint32_t maxFocus;
		uint32_t currentFocus;
		uint32_t maxWillpower;
		uint32_t currentWillpower;

		uint64_t objectId;
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