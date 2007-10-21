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

#include <osSOEProtocol/export.h>
#include <boost/shared_ptr.hpp>
#include <osSOEProtocol/object.h>
namespace osSOEProtocol
{
	class OS_SOEPROTOCOL_EXPORT CreatureObject : public Object
	{
	public:
		CreatureObject() {
			m_posture = 0;
			m_targetId=0;
		}
		virtual ~CreatureObject(){}

		uint64 getTargetId() { return m_targetId; }
		void setTargetId(uint64 targetId) { m_targetId = targetId; }
		
		std::string getAppearance() { return m_appearance; }
		void setAppearance(std::string appearance) { m_appearance = appearance; }
		
		std::string getPlanet() { return m_planet; }
		void setPlanet(std::string planet) { m_planet = planet; }
		
		std::string getMood() { return m_mood; }
		void setMood(std::string mood) { m_mood = mood; }
		
		uint8 getPosture() { return m_posture; }
		void setPosture(uint8 posture) { m_posture = posture; }
		
		uint32 getMaxHealth() { return m_maxHealth; }
		void setMaxHealth(uint32 health) { m_maxHealth = health; }
		
		uint32 getMaxStrength() { return m_maxStrength; }
		void setMaxStrength(uint32 strength) { m_maxStrength = strength; }
		
		uint32 getMaxConstitution() { return m_maxConstitution; }
		void setMaxConstitution(uint32 constitution) { m_maxConstitution = constitution; }
	
		uint32 getMaxAction() { return m_maxAction; }
		void setMaxAction(uint32 action) { m_maxAction = action; }

		uint32 getMaxQuickness() { return m_maxQuickness; }
		void setMaxQuickness(uint32 quickness) { m_maxQuickness = quickness; }

		uint32 getMaxStamina() { return m_maxStamina; }
		void setMaxStamina(uint32 stamina) { m_maxStamina = stamina; }

		uint32 getMaxMind() { return m_maxMind; }
		void setMaxMind(uint32 mind) { m_maxMind = mind; }

		uint32 getMaxFocus() { return m_maxFocus; }
		void setMaxFocus(uint32 focus) { m_maxFocus = focus; }

		uint32 getMaxWillpower() { return m_maxWillpower; }
		void setMaxWillpower(uint32 willpower) { m_maxWillpower = willpower; }
		
		uint32 getCurrentHealth() { return m_currentHealth; }
		void setCurrentHealth(uint32 health) { m_currentHealth = health; }
		
		uint32 getCurrentStrength() { return m_currentStrength; }
		void setCurrentStrength(uint32 strength) { m_currentStrength = strength; }
		
		uint32 getCurrentConstitution() { return m_currentConstitution; }
		void setCurrentConstitution(uint32 constitution) { m_currentConstitution = constitution; }
	
		uint32 getCurrentAction() { return m_currentAction; }
		void setCurrentAction(uint32 action) { m_currentAction = action; }

		uint32 getCurrentQuickness() { return m_currentQuickness; }
		void setCurrentQuickness(uint32 quickness) { m_currentQuickness = quickness; }

		uint32 getCurrentStamina() { return m_currentStamina; }
		void setCurrentStamina(uint32 stamina) { m_currentStamina = stamina; }

		uint32 getCurrentMind() { return m_currentMind; }
		void setCurrentMind(uint32 mind) { m_currentMind = mind; }

		uint32 getCurrentFocus() { return m_currentFocus; }
		void setCurrentFocus(uint32 focus) { m_currentFocus = focus; }

		uint32 getCurrentWillpower() { return m_currentWillpower; }
		void setCurrentWillpower(uint32 willpower) { m_currentWillpower = willpower; }
		
		
		uint32 getHealthWounds() { return m_healthWounds; }
		void setHealthWounds(uint32 health) { m_healthWounds = health; }
		
		uint32 getStrengthWounds() { return m_strengthWounds; }
		void setStrengthWounds(uint32 strength) { m_strengthWounds = strength; }
		
		uint32 getConstitutionWounds() { return m_constitutionWounds; }
		void setConstitutionWounds(uint32 constitution) { m_constitutionWounds = constitution; }
	
		uint32 getActionWounds() { return m_actionWounds; }
		void setActionWounds(uint32 action) { m_actionWounds = action; }

		uint32 getQuicknessWounds() { return m_quicknessWounds; }
		void setQuicknessWounds(uint32 quickness) { m_quicknessWounds = quickness; }

		uint32 getStaminaWounds() { return m_staminaWounds; }
		void setStaminaWounds(uint32 stamina) { m_staminaWounds = stamina; }

		uint32 getMindWounds() { return m_mindWounds; }
		void setMindWounds(uint32 mind) { m_mindWounds = mind; }

		uint32 getFocusWounds() { return m_focusWounds; }
		void setFocusWounds(uint32 focus) { m_focusWounds = focus; }

		uint32 getWillpowerWounds() { return m_willpowerWounds; }
		void setWillpowerWounds(uint32 willpower) { m_willpowerWounds = willpower; }
		
		
		uint32 getHealthModifiers() { return m_healthModifiers; }
		void setHealthModifiers(uint32 health) { m_healthModifiers = health; }
		
		uint32 getStrengthModifiers() { return m_strengthModifiers; }
		void setStrengthModifiers(uint32 strength) { m_strengthModifiers = strength; }
		
		uint32 getConstitutionModifiers() { return m_constitutionModifiers; }
		void setConstitutionModifiers(uint32 constitution) { m_constitutionModifiers = constitution; }
	
		uint32 getActionModifiers() { return m_actionModifiers; }
		void setActionModifiers(uint32 action) { m_actionModifiers = action; }

		uint32 getQuicknessModifiers() { return m_quicknessModifiers; }
		void setQuicknessModifiers(uint32 quickness) { m_quicknessModifiers = quickness; }

		uint32 getStaminaModifiers() { return m_staminaModifiers; }
		void setStaminaModifiers(uint32 stamina) { m_staminaModifiers = stamina; }

		uint32 getMindModifiers() { return m_mindModifiers; }
		void setMindModifiers(uint32 mind) { m_mindModifiers = mind; }

		uint32 getFocusModifiers() { return m_focusModifiers; }
		void setFocusModifiers(uint32 focus) { m_focusModifiers = focus; }

		uint32 getWillpowerModifiers() { return m_willpowerModifiers; }
		void setWillpowerModifiers(uint32 willpower) { m_willpowerModifiers = willpower; }

		uint32 getCreatureType() { return m_creatureType; }
		void setCreatureType(uint32 creatureType) { m_creatureType = creatureType; }

		uint32 getFactionAlignment() { return m_factionAlignment; }
		void setFactionAlignment(uint32 factionAlignment) { m_factionAlignment = factionAlignment; }

		uint32 getBattleFatigue() { return m_battleFatigue; }
		void setBattleFatigue(uint32 battleFatigue) { m_battleFatigue = battleFatigue; }

	private:
		std::string m_appearance;
		std::string m_planet;
		std::string m_mood;

		uint32 m_creatureType;
		uint32 m_factionAlignment;
		uint32 m_battleFatigue;
	
		uint32 m_maxHealth;
		uint32 m_maxStrength;
		uint32 m_maxConstitution;
		uint32 m_maxAction;
		uint32 m_maxQuickness;
		uint32 m_maxStamina;
		uint32 m_maxMind;
		uint32 m_maxFocus;
		uint32 m_maxWillpower;
	
		uint32 m_currentHealth;
		uint32 m_currentStrength;
		uint32 m_currentConstitution;
		uint32 m_currentAction;
		uint32 m_currentQuickness;
		uint32 m_currentStamina;
		uint32 m_currentMind;
		uint32 m_currentFocus;
		uint32 m_currentWillpower;
	
		uint32 m_healthWounds;
		uint32 m_strengthWounds;
		uint32 m_constitutionWounds;
		uint32 m_actionWounds;
		uint32 m_quicknessWounds;
		uint32 m_staminaWounds;
		uint32 m_mindWounds;
		uint32 m_focusWounds;
		uint32 m_willpowerWounds;
	
		uint32 m_healthModifiers;
		uint32 m_strengthModifiers;
		uint32 m_constitutionModifiers;
		uint32 m_actionModifiers;
		uint32 m_quicknessModifiers;
		uint32 m_staminaModifiers;
		uint32 m_mindModifiers;
		uint32 m_focusModifiers;
		uint32 m_willpowerModifiers;
		uint64 m_targetId;

		uint8 m_posture;
	};

	typedef OS_SOEPROTOCOL_EXPORT boost::shared_ptr<CreatureObject> CreatureObjectPtr;
}

#endif // OPENSWG_SOEPROTOCOL_CREATUREOBJECT