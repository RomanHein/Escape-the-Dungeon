#pragma once

#include <string>

#include "damage_type.h"
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
	
	// Deals basic damage to a target, creates a damage event.
	double dealDamage(Entity& user, Entity& target, std::vector<std::string>& events);
	// Reduces user's stamina by spell's stamina cost. Creates event.
	void reduceStamina(Entity& user, std::vector<std::string>& events);
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

