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

#ifndef OPENSWG_SOEPROTOCOL_CREATUREOBJECT
#define OPENSWG_SOEPROTOCOL_CREATUREOBJECT

#include <boost/shared_ptr.hpp>
#include <osSOEProtocol/object.h>

namespace osSOEProtocol
{
	class CreatureObject : public Object
	{
	public:
		CreatureObject() {
			m_posture = 0;
			m_targetId=0;
		}
		virtual ~CreatureObject(){}

		uint64_t getTargetId() { return m_targetId; }
		void setTargetId(uint64_t targetId) { m_targetId = targetId; }
		
		std::string getAppearance() { return m_appearance; }
		void setAppearance(std::string appearance) { m_appearance = appearance; }
		
		std::string getPlanet() { return m_planet; }
		void setPlanet(std::string planet) { m_planet = planet; }
		
		std::string getMood() { return m_mood; }
		void setMood(std::string mood) { m_mood = mood; }
		
		uint8_t getPosture() { return m_posture; }
		void setPosture(uint8_t posture) { m_posture = posture; }
		
		uint32_t getMaxHealth() { return m_maxHealth; }
		void setMaxHealth(uint32_t health) { m_maxHealth = health; }
		
		uint32_t getMaxStrength() { return m_maxStrength; }
		void setMaxStrength(uint32_t strength) { m_maxStrength = strength; }
		
		uint32_t getMaxConstitution() { return m_maxConstitution; }
		void setMaxConstitution(uint32_t constitution) { m_maxConstitution = constitution; }
	
		uint32_t getMaxAction() { return m_maxAction; }
		void setMaxAction(uint32_t action) { m_maxAction = action; }

		uint32_t getMaxQuickness() { return m_maxQuickness; }
		void setMaxQuickness(uint32_t quickness) { m_maxQuickness = quickness; }

		uint32_t getMaxStamina() { return m_maxStamina; }
		void setMaxStamina(uint32_t stamina) { m_maxStamina = stamina; }

		uint32_t getMaxMind() { return m_maxMind; }
		void setMaxMind(uint32_t mind) { m_maxMind = mind; }

		uint32_t getMaxFocus() { return m_maxFocus; }
		void setMaxFocus(uint32_t focus) { m_maxFocus = focus; }

		uint32_t getMaxWillpower() { return m_maxWillpower; }
		void setMaxWillpower(uint32_t willpower) { m_maxWillpower = willpower; }
		
		uint32_t getCurrentHealth() { return m_currentHealth; }
		void setCurrentHealth(uint32_t health) { m_currentHealth = health; }
		
		uint32_t getCurrentStrength() { return m_currentStrength; }
		void setCurrentStrength(uint32_t strength) { m_currentStrength = strength; }
		
		uint32_t getCurrentConstitution() { return m_currentConstitution; }
		void setCurrentConstitution(uint32_t constitution) { m_currentConstitution = constitution; }
	
		uint32_t getCurrentAction() { return m_currentAction; }
		void setCurrentAction(uint32_t action) { m_currentAction = action; }

		uint32_t getCurrentQuickness() { return m_currentQuickness; }
		void setCurrentQuickness(uint32_t quickness) { m_currentQuickness = quickness; }

		uint32_t getCurrentStamina() { return m_currentStamina; }
		void setCurrentStamina(uint32_t stamina) { m_currentStamina = stamina; }

		uint32_t getCurrentMind() { return m_currentMind; }
		void setCurrentMind(uint32_t mind) { m_currentMind = mind; }

		uint32_t getCurrentFocus() { return m_currentFocus; }
		void setCurrentFocus(uint32_t focus) { m_currentFocus = focus; }

		uint32_t getCurrentWillpower() { return m_currentWillpower; }
		void setCurrentWillpower(uint32_t willpower) { m_currentWillpower = willpower; }
		
		
		uint32_t getHealthWounds() { return m_healthWounds; }
		void setHealthWounds(uint32_t health) { m_healthWounds = health; }
		
		uint32_t getStrengthWounds() { return m_strengthWounds; }
		void setStrengthWounds(uint32_t strength) { m_strengthWounds = strength; }
		
		uint32_t getConstitutionWounds() { return m_constitutionWounds; }
		void setConstitutionWounds(uint32_t constitution) { m_constitutionWounds = constitution; }
	
		uint32_t getActionWounds() { return m_actionWounds; }
		void setActionWounds(uint32_t action) { m_actionWounds = action; }

		uint32_t getQuicknessWounds() { return m_quicknessWounds; }
		void setQuicknessWounds(uint32_t quickness) { m_quicknessWounds = quickness; }

		uint32_t getStaminaWounds() { return m_staminaWounds; }
		void setStaminaWounds(uint32_t stamina) { m_staminaWounds = stamina; }

		uint32_t getMindWounds() { return m_mindWounds; }
		void setMindWounds(uint32_t mind) { m_mindWounds = mind; }

		uint32_t getFocusWounds() { return m_focusWounds; }
		void setFocusWounds(uint32_t focus) { m_focusWounds = focus; }

		uint32_t getWillpowerWounds() { return m_willpowerWounds; }
		void setWillpowerWounds(uint32_t willpower) { m_willpowerWounds = willpower; }
		
		
		uint32_t getHealthModifiers() { return m_healthModifiers; }
		void setHealthModifiers(uint32_t health) { m_healthModifiers = health; }
		
		uint32_t getStrengthModifiers() { return m_strengthModifiers; }
		void setStrengthModifiers(uint32_t strength) { m_strengthModifiers = strength; }
		
		uint32_t getConstitutionModifiers() { return m_constitutionModifiers; }
		void setConstitutionModifiers(uint32_t constitution) { m_constitutionModifiers = constitution; }
	
		uint32_t getActionModifiers() { return m_actionModifiers; }
		void setActionModifiers(uint32_t action) { m_actionModifiers = action; }

		uint32_t getQuicknessModifiers() { return m_quicknessModifiers; }
		void setQuicknessModifiers(uint32_t quickness) { m_quicknessModifiers = quickness; }

		uint32_t getStaminaModifiers() { return m_staminaModifiers; }
		void setStaminaModifiers(uint32_t stamina) { m_staminaModifiers = stamina; }

		uint32_t getMindModifiers() { return m_mindModifiers; }
		void setMindModifiers(uint32_t mind) { m_mindModifiers = mind; }

		uint32_t getFocusModifiers() { return m_focusModifiers; }
		void setFocusModifiers(uint32_t focus) { m_focusModifiers = focus; }

		uint32_t getWillpowerModifiers() { return m_willpowerModifiers; }
		void setWillpowerModifiers(uint32_t willpower) { m_willpowerModifiers = willpower; }

		uint32_t getCreatureType() { return m_creatureType; }
		void setCreatureType(uint32_t creatureType) { m_creatureType = creatureType; }

		uint32_t getFactionAlignment() { return m_factionAlignment; }
		void setFactionAlignment(uint32_t factionAlignment) { m_factionAlignment = factionAlignment; }

		uint32_t getBattleFatigue() { return m_battleFatigue; }
		void setBattleFatigue(uint32_t battleFatigue) { m_battleFatigue = battleFatigue; }

	private:
		std::string m_appearance;
		std::string m_planet;
		std::string m_mood;

		uint32_t m_creatureType;
		uint32_t m_factionAlignment;
		uint32_t m_battleFatigue;
	
		uint32_t m_maxHealth;
		uint32_t m_maxStrength;
		uint32_t m_maxConstitution;
		uint32_t m_maxAction;
		uint32_t m_maxQuickness;
		uint32_t m_maxStamina;
		uint32_t m_maxMind;
		uint32_t m_maxFocus;
		uint32_t m_maxWillpower;
	
		uint32_t m_currentHealth;
		uint32_t m_currentStrength;
		uint32_t m_currentConstitution;
		uint32_t m_currentAction;
		uint32_t m_currentQuickness;
		uint32_t m_currentStamina;
		uint32_t m_currentMind;
		uint32_t m_currentFocus;
		uint32_t m_currentWillpower;
	
		uint32_t m_healthWounds;
		uint32_t m_strengthWounds;
		uint32_t m_constitutionWounds;
		uint32_t m_actionWounds;
		uint32_t m_quicknessWounds;
		uint32_t m_staminaWounds;
		uint32_t m_mindWounds;
		uint32_t m_focusWounds;
		uint32_t m_willpowerWounds;
	
		uint32_t m_healthModifiers;
		uint32_t m_strengthModifiers;
		uint32_t m_constitutionModifiers;
		uint32_t m_actionModifiers;
		uint32_t m_quicknessModifiers;
		uint32_t m_staminaModifiers;
		uint32_t m_mindModifiers;
		uint32_t m_focusModifiers;
		uint32_t m_willpowerModifiers;
		uint64_t m_targetId;

		uint8_t m_posture;
	};

	typedef boost::shared_ptr<CreatureObject> CreatureObjectPtr;
}

#endif // OPENSWG_SOEPROTOCOL_CREATUREOBJECT