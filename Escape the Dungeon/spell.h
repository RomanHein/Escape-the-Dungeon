// spell.h
//
// Base class for all spells in the game

#pragma once

#include <string>

#include "damage_type.h"
#include "hit_info.h"
#include "item.h"

class Entity;

class Spell : public Item
{
private:
	double damage_;
	DamageType damageType_;

protected:
	//
	// === Protected Methods ===
	//

	// Deals basic spell damage.
	HitInfo dealDamage(Entity& target);

	// Creates an attack event.
	std::string makeDamageEvent(const HitInfo& info, const Entity& target);

	// Reduces user's stamina by spell's stamina cost. Creates event.
	void reduceStamina(Entity& user, std::vector<std::string>& events);

	// Returns a stamina consumption event.
	std::string makeStaminaEvent(int lostStamina, const Entity& user);

	// Builds a basic description of a spell.
	std::string getBasicDescription();

public:
	//
	// === Constructor & Destructor ===
	//

	explicit Spell(const std::string& name, int staminaCost, double damage, DamageType damageType);

	//
	// === Getters & Setters ===
	//

	double getDamage() const;
	DamageType getDamageType() const;
};

