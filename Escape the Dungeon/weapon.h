#pragma once

#include <string>
#include <vector>

#include "damage_type.h"
#include "hit_info.h"
#include "item.h"

class Entity;

class Weapon : public Item
{
private:
	double damage_;
	DamageType damageType_;
	double critChance_, critDamage_;
	double hitChance_;


protected:
	//
	// === Protected Methods ===
	//

	// Ich hasse diese dumme kacke, es sieht nicht nur kacke aus sondern es ist auch einfach nur kacke.
	// Kein Bock Structs zu machen weil sonst müsste man 1000 machen ICH HASSE DICH WEAPON HAHWDHHAWHDHAWHDHWAD

	// Deals basic damage to a target, creates a damage event.
	void dealDamage(Entity& user, Entity& target, std::vector<std::string>& events);
	// Evaluates damage event.
	//std::string makeDamageEvent(const HitInfo& info, const Entity& target);
	// Reduces user's stamina by spell's stamina cost. Creates event.
	void reduceStamina(Entity& user, std::vector<std::string>& events);
	// Builds a basic description of a spell.
	std::string getBasicDescription();

public:
	//
	// === Constructor & Destructor ===
	//

	explicit Weapon(
		const std::string name, 
		int staminaCost, 
		double damage, 
		DamageType damageType, 
		double critChance, 
		double critDamage,
		double hitChance
	);

	//
	// === Getters & Setters ===
	//

	double getDamage() const;
	DamageType getDamageType() const;
	double getCritChance() const;
	double getCritDamage() const;
};

