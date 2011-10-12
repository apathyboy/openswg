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

#include <gsServer/opcodehandler.h>
#include <gsServer/session.h>
#include <gsCore/datastore.h>
#include <gsCore/timing.h>
#include <osSOEProtocol/characteroptionsmessage.h>
#include <osSOEProtocol/charactercreationrequest.h>
#include <osSOEProtocol/assigncharacteridmessage.h>
#include <osSOEProtocol/soelayermessages.h>
#include <osSOEProtocol/tangibleobjectproxy.h>
#include <osSOEProtocol/objectpropertytypes.h>

#include <osSOEProtocol/opcodes.h>

#include <osZonePreCU/charactercreationmanager.h>

using namespace gsCore;
using namespace gsNetwork;
using namespace gsServer;
using namespace osSOEProtocol;
using namespace osZonePreCU;

CharacterCreationManager::CharacterCreationManager()
{
	m_idChunk = 0;
}

void CharacterCreationManager::loadCreationItems()
{
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT creation_items.id, "
          << "       creation_items.profession, "
		  << "		 creation_items.species, "
          << "       creation_items.gender, "
          << "       creation_items.template "
          << "FROM creation_items";
	
        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this] (const mysqlpp::Row& row) 
            {  
				CreationItem item;
				item.id = (uint32_t)row["id"];
				item.profession = (std::string)row["profession"];
				item.species = (std::string)row["species"];
				item.gender = (std::string)row["gender"];
				item.templateItem = (std::string)row["template"];

				m_creationItems.push_back(item);
			});
		}
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
		return;
	}
}

void CharacterCreationManager::loadRacialMods()
{
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT racial_mods.id, "
          << "       racial_mods.male_template, "
		  << "		 racial_mods.female_template, "
          << "       racial_mods.health, "
          << "       racial_mods.strength, "
          << "       racial_mods.constitution, "
          << "       racial_mods.action, "
          << "       racial_mods.quickness, "
          << "       racial_mods.stamina, "
          << "       racial_mods.mind, "
          << "       racial_mods.focus, "
          << "       racial_mods.willpower "
          << "FROM racial_mods";
	
        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this] (const mysqlpp::Row& row) 
            {  
				RacialMod mod;
				mod.id = (uint32_t)row["id"];
				mod.maleTemplate = (std::string)row["male_template"];
				mod.femaleTemplate = (std::string)row["female_template"];
				mod.health = (uint32_t)row["health"];
				mod.strength = (uint32_t)row["strength"];
				mod.constitution = (uint32_t)row["constitution"];
				mod.action = (uint32_t)row["action"];
				mod.quickness = (uint32_t)row["quickness"];
				mod.stamina = (uint32_t)row["stamina"];
				mod.mind = (uint32_t)row["mind"];
				mod.focus = (uint32_t)row["focus"];
				mod.willpower = (uint32_t)row["willpower"];

				m_racialMods.push_back(mod);
			});
		}
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
		return;
	}
}

void CharacterCreationManager::loadProfessionMods()
{
	try
    {
		mysqlpp::Query q = Datastore::getGalaxyDB().query();

		q << "SELECT profession_mods.id, "
          << "       profession_mods.profession, "
          << "       profession_mods.health, "
          << "       profession_mods.strength, "
          << "       profession_mods.constitution, "
          << "       profession_mods.action, "
          << "       profession_mods.quickness, "
          << "       profession_mods.stamina, "
          << "       profession_mods.mind, "
          << "       profession_mods.focus, "
          << "       profession_mods.willpower "
          << "FROM profession_mods";
	
        mysqlpp::StoreQueryResult result = q.store();
                
		if (result)
        {
            std::for_each(begin(result), end(result), [this] (const mysqlpp::Row& row) 
            {  
				ProfessionMod mod;
				mod.id = (uint32_t)row["id"];
				mod.profession = (std::string)row["profession"];
				mod.health = (uint32_t)row["health"];
				mod.strength = (uint32_t)row["strength"];
				mod.constitution = (uint32_t)row["constitution"];
				mod.action = (uint32_t)row["action"];
				mod.quickness = (uint32_t)row["quickness"];
				mod.stamina = (uint32_t)row["stamina"];
				mod.mind = (uint32_t)row["mind"];
				mod.focus = (uint32_t)row["focus"];
				mod.willpower = (uint32_t)row["willpower"];

				m_professionMods.push_back(mod);
			});
		}
    }
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
		return;
	}
}

void CharacterCreationManager::initialize()
{
	loadProfessionMods();
	loadRacialMods();
	loadCreationItems();
}

void CharacterCreationManager::registerOpcodes(gsServer::OpcodeFactory* factory)
{
	CBFunctor2<Session*, BinaryPacketPtr> handler = makeFunctor((HandlerFunctor)0, *this, &CharacterCreationManager::handleCharacterCreationRequest);	
	factory->addOpcodeHandler(CMSG_NOTIFY_SESSION, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	handler = makeFunctor((HandlerFunctor)0, *this, &CharacterCreationManager::handleCharacterOptionsValidation);	
	factory->addOpcodeHandler(CMSG_GEN_CHAR_NAME, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));

	handler = makeFunctor((HandlerFunctor)0, *this, &CharacterCreationManager::handleCreateCharacter);	
	factory->addOpcodeHandler(CMSG_CREATE_CHAR, OpcodeHandlerPtr(GS_NEW OpcodeHandler(handler)));
}



void CharacterCreationManager::handleCharacterCreationRequest(gsServer::Session* session, gsNetwork::BinaryPacketPtr message) 
{
	boost::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);
	
	boost::shared_ptr<CharacterOptionsMessage> response(GS_NEW CharacterOptionsMessage());
	response->availableSlots = 1; // Pull from db
	session->sendToRemote(response);
}

void CharacterCreationManager::handleCharacterOptionsValidation(gsServer::Session* session, gsNetwork::BinaryPacketPtr message) 
{
	boost::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);
}

void CharacterCreationManager::handleCreateCharacter(gsServer::Session* session, gsNetwork::BinaryPacketPtr message) 
{
	boost::shared_ptr<CharacterCreationRequest> creationRequest(GS_NEW CharacterCreationRequest(message));
	creationRequest->unserialize();

	boost::shared_ptr<OkMessage> ok(GS_NEW OkMessage());
	ok->sequence = session->getClientSequence();
	session->sendToRemote(ok);

	uint64_t objectId = generateObjectId();
	uint64_t characterId = generateObjectId();

	boost::optional<RacialMod> racialMod = findRacialMod(creationRequest->race);
	if (! racialMod)
		return;

	boost::optional<ProfessionMod> professionMod = findProfessionMod(creationRequest->profession);
	if (! professionMod)
		return;

	try
    {
		mysqlpp::Query q = Datastore::getStationDB().query();

        q << "INSERT INTO `characters` (`account_id`, `galaxy_id`, `zone_id`, "
		  << "  `object_id`, `firstname`, `surname`, `model`, `category`, `type`, "
		  << "  `appearance`, `hair`, `hair_data`, `biography`, "
		  << "  `health`, `strength`, `constitution`, `action`, `quickness`, "
		  << "  `stamina`, `mind`, `focus`, `willpower`, "
          << "  `planet`, `quaternion_x`, `quaternion_y`, `quaternion_z`, `quaternion_w`, "
          << "  `position_x`, `position_y`, `position_z`, "
          << "  `scale`, `created_on`, `state`) "
		  << "VALUES (" << session->getAccountId() << ", "
          << 1 << ", " // Hardcoded galaxy id
		  << 1 << ", " // Hardcoded zone id
		  << objectId << ", "
          << mysqlpp::quote << creationRequest->firstname << ", "
          << mysqlpp::quote << creationRequest->surname << ", "
		  << mysqlpp::quote << creationRequest->race << ", "
		  << mysqlpp::quote << creationRequest->category << ", " // Hardcoded object category
		  << mysqlpp::quote << creationRequest->type << ", " // Hardcoded object type
          << mysqlpp::quote << creationRequest->appearance << ", "
          << mysqlpp::quote << creationRequest->hair << ", "
          << mysqlpp::quote << creationRequest->hairData << ", "
          << mysqlpp::quote << std::string(creationRequest->biography.begin(), creationRequest->biography.end()) << ", "
		  << (*racialMod).health+(*professionMod).health << ", "
		  << (*racialMod).strength+(*professionMod).strength << ", "
		  << (*racialMod).constitution+(*professionMod).constitution << ", "
		  << (*racialMod).action+(*professionMod).action << ", "
		  << (*racialMod).quickness+(*professionMod).quickness << ", "
		  << (*racialMod).stamina+(*professionMod).stamina << ", "
		  << (*racialMod).mind+(*professionMod).mind << ", "
		  << (*racialMod).focus+(*professionMod).focus << ", "
		  << (*racialMod).willpower+(*professionMod).willpower << ", "
		  << mysqlpp::quote << std::string("naboo") << ", " // Hardcoded planet id
          << 0 << ", " // Qx
          << 0 << ", " // Qy
          << 0 << ", " // Qz
          << 0 << ", " // Qw
          << 1443 << ", " // Px
          << 13 << ", " // Py
          << 2771 << ", " // Pz
          << creationRequest->scale << ", "
          << "NOW(), "
          << 1 << ")"; // Active subscriber state

		mysqlpp::SimpleResult result = q.execute();

		if (! result)
        {
			Log::getMainLog().error("Unable to create character [%s]", creationRequest->fullname.c_str());
			return;
        }

		characterId = (uint64_t)result.insert_id;

		createCharacterItems(objectId, creationRequest->profession, creationRequest->race);
	}
	catch (const mysqlpp::Exception& er)
    {
		// Catch-all for any other MySQL++ exceptions
        LOG(ERROR) << "ERROR: " << er.what();
		return;
	}

	boost::shared_ptr<AssignCharacterIdMessage> response(GS_NEW AssignCharacterIdMessage());
	response->characterId = characterId; // Pull from db
	session->sendToRemote(response);
}

boost::optional<ProfessionMod> CharacterCreationManager::findProfessionMod(const std::string& profession)
{
	boost::optional<ProfessionMod> mod;
	for (std::vector<ProfessionMod>::iterator itor = m_professionMods.begin();
		itor != m_professionMods.end(); ++itor)
	{ 
		if (profession.compare((*itor).profession) == 0)
		{
			mod = (*itor);
		}
	}

	return mod;
}

boost::optional<RacialMod> CharacterCreationManager::findRacialMod(const std::string& race)
{
	boost::optional<RacialMod> mod;
	std::string search = race.substr(race.find_first_of("_")+1, race.find_last_of(".")-(race.find_first_of("_")+1));

	for (std::vector<RacialMod>::iterator itor = m_racialMods.begin();
		itor != m_racialMods.end(); ++itor)
	{ 
		if (search.compare((*itor).maleTemplate) == 0 ||
			search.compare((*itor).femaleTemplate) == 0)
		{
			mod = (*itor);
		}
	}

	return mod;
}

void CharacterCreationManager::createCharacterItems(uint64_t playerId, const std::string& profession, const std::string& race)
{
	// Get the species.
	std::string::size_type pos = race.find_first_of("_");
	pos +=1;
	std::string::size_type endPos = race.find_last_of("_");
	std::string species = race.substr(pos, endPos - pos);
	
	pos = race.find_last_of("_");
	pos +=1;
	endPos = race.find_first_of(".");
	std::string gender = race.substr(pos, endPos - pos);

	for (std::vector<CreationItem>::iterator itor = m_creationItems.begin();
		itor != m_creationItems.end(); ++itor)
	{ 
		if (profession.compare((*itor).profession) == 0 &&
			species.compare((*itor).species) == 0 &&
			gender.compare((*itor).gender) == 0)
		{
			boost::shared_ptr<TangibleObjectProxy> item(GS_NEW TangibleObjectProxy);
			item->createFromTemplate((*itor).templateItem);
			item->getPropertyAs<Uint64ObjectProperty*>(std::string("ObjectId"))->setValue(generateObjectId());
			item->getPropertyAs<Uint64ObjectProperty*>(std::string("ParentId"))->setValue(playerId);
			item->getPropertyAs<UintObjectProperty*>(std::string("State"))->setValue(1);
			item->getPropertyAs<BooleanObjectProperty*>(std::string("Equipped"))->setValue(true);
			item->store();
		}
	}
}

