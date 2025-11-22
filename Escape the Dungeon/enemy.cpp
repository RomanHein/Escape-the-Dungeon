#include "enemy.h"

#include "math_utils.h"
#include "goblin.h"

// === Static Methods ===

std::unique_ptr<Enemy> Enemy::createRandom()
{
	switch (utils::math::randomInt(1, 1))
	{
	case 1:
		return std::make_unique<Goblin>();

	default:
		return nullptr;
	}
}

// === Constructor & Destructor ===

Enemy::Enemy(
	const std::string& name, 
	double initialHealth, 
	int initialStamina, 
	double dodgeChance, 
	const std::vector<DefenseProfile>& defenseProfiles,
	std::vector<std::unique_ptr<Item>>&& inventory
) :
	Entity(name, initialHealth, initialStamina, dodgeChance, defenseProfiles, std::move(inventory))
{ }