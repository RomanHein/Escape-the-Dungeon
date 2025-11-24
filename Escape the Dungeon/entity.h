// entity.h
//
// Base class for all enemies in the game.

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "damage_type.h"
#include "defense_profile.h"
#include "take_damage_result.h"

class Effect;
class Item;

class Entity
{
private:
	std::string name_;
	double health_, maxHealth_;
	int stamina_, maxStamina_;
	double dodgeChance_;
	std::vector<DefenseProfile> defenseProfiles_;
	std::vector<std::unique_ptr<Effect>> effects_;
	std::vector<std::unique_ptr<Item>> inventory_;

public:
	//
	// === Constructor & Destructor ===
	//

	explicit Entity(
		const std::string& name, 
		double initialHealth, 
		int initialStamina, 
		double dodgeChance, 
		const std::vector<DefenseProfile>& defenseProfile,
		std::vector<std::unique_ptr<Item>>&& inventory
	);

	virtual ~Entity();

	//
	// === Public Methods ===
	//

	// Reduces health, decreasing/increasing damage depending on entity's defense profiles.
	TakeDamageResult takeDamage(DamageType damageType, double amount, bool dodgeable);

	// Activates all effects once, removing expired effects afterwards.
	std::vector<std::string> processEffects();

	// Returns item with given name from entity's inventory.
	Item* getItem(const std::string& name);

	// Restores health by given amount, can't exceeed max health.
	void heal(double amount);

	// Reduces stamina, can't fall below 0.
	void consumeStamina(int amount);

	// Restores stamina, can't exceed max stamina.
	void restoreStamina(int amount);

	// Adds an effect.
	void addEffect(std::unique_ptr<Effect> effect);

	// Removes an item from the inventory.
	void removeItem(const std::string& name);

	//
	// === Predicate Methods ===
	//

	// Returns true if the entity is alive.
	bool isAlive() const;

	// Returns true if stamina doesn't fall below 0 after decreasing it by stamina cost.
	bool canPerform(int staminaCost) const;

	// Returns true if entity has item with given name. Isn't case sensitive.
	bool hasItem(const std::string& name) const;

	// Returns true if entity has damage type vulnerability.
	bool isWeakTo(DamageType damageType) const;

	//
	// === Getters & Setters ===
	//

	const std::string& getName() const;
	double getHealth() const;
	double getMaxHealth() const;
	int getStamina() const;
	int getMaxStamina() const;
	double getDodgeChance() const;
	const std::vector<DefenseProfile>& getDefenseProfiles() const;
	const std::vector<std::unique_ptr<Item>>& getInventory() const;
	const std::vector<std::unique_ptr<Effect>>& getEffects() const;
};

