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

#ifndef OPENSWG_ZONEPRECU_CHARACTERCREATIONMANAGER
#define OPENSWG_ZONEPRECU_CHARACTERCREATIONMANAGER

#include <gsCore/timing.h>
#include <gsNetwork/binarypacket.h>

namespace gsServer
{
	class OpcodeFactory;
	class Session;
}

namespace osZonePreCU
{
	struct CreationItem
	{
		uint32 id;
		std::string profession;
		std::string species;
		std::string gender;
		std::string templateItem;
	};

	struct ProfessionMod
	{
		uint32 id;
		std::string profession;
		uint32 health;
		uint32 strength;
		uint32 constitution;
		uint32 action;
		uint32 quickness;
		uint32 stamina;
		uint32 mind;
		uint32 focus;
		uint32 willpower;
	};

	struct RacialMod
	{
		uint32 id;
		std::string maleTemplate;
		std::string femaleTemplate;
		uint32 health;
		uint32 strength;
		uint32 constitution;
		uint32 action;
		uint32 quickness;
		uint32 stamina;
		uint32 mind;
		uint32 focus;
		uint32 willpower;
	};

	class CharacterCreationManager //: public GameManager 
	// @NOTE: Extract common functionality to a GameManager base class.
	{
	public:
		CharacterCreationManager();

	protected:
		uint32 m_idChunk;

	public: // OPCODE HANDLING
		virtual void registerOpcodes(gsServer::OpcodeFactory* factory);
	
		void handleCharacterCreationRequest(gsServer::Session* session, gsNetwork::BinaryPacketPtr message);
		void handleCharacterOptionsValidation(gsServer::Session* session, gsNetwork::BinaryPacketPtr message);
		void handleCreateCharacter(gsServer::Session* session, gsNetwork::BinaryPacketPtr message);

	public:
		void initialize();

	protected:
		void loadCreationItems();
		void loadRacialMods();
		void loadProfessionMods();
		std::vector<RacialMod> m_racialMods;
		std::vector<ProfessionMod> m_professionMods;		
		std::vector<CreationItem> m_creationItems;
	
		boost::optional<ProfessionMod> findProfessionMod(const std::string& profession);
		boost::optional<RacialMod> findRacialMod(const std::string& race);
		void createCharacterItems(uint64 playerId, const std::string& profession, const std::string& race);
	};
}

#endif // OPENSWG_ZONEPRECU_CHARACTERCREATIONMANAGER

