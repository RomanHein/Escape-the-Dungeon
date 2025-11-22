#pragma once

#include <string>

#include "effect.h"
#include "damage_type.h"

class Entity;

class DoT : public Effect
{
private:
	double damage_;
	DamageType damageType_;

protected:
	//
	// === Protected Methods ===
	//

	// Deals basic damage.
	std::string dealDamage(Entity& target);

public:
	//
	// === Constructor & Destructor ===
	//

	explicit DoT(const std::string& name, int duration, double damage, DamageType damageType);

	//
	// === Getters & Setters ===
	//

	double getDamage() const;
	DamageType getDamageType() const;
};

