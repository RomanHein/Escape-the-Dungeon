#pragma once

#include <memory>
#include <string>
#include <vector>

#include "defense_profile.h"
#include "entity.h"

class Player;
class Item;

class Enemy : public Entity
{
public:
	// === Constructor & Destructor ===

	explicit Enemy(
		const std::string& name, 
		double initialHealth, 
		int initialStamina, 
		double dodgeChance, 
		const std::vector<DefenseProfile>& defenseProfiles,
		std::vector<std::unique_ptr<Item>>&& inventory
	);

	// === Static Methods ===

	// Returns a random enemy.
	static std::unique_ptr<Enemy> createRandom();

	// === Public Methods ===

	// Forces the enemy to make a turn based on the game state.
	virtual std::vector<std::string> makeTurn(Player& player) = 0;
};

