#include "enemy.h"

#include "math_utils.h"
#include "goblin.h"
#include "demon.h"
#include "golem.h"

//
// === Static Methods ===
//

std::unique_ptr<Enemy> Enemy::createRandom()
{
	switch (core::utils::math::randomInt(1, 3))
	{
	case 1:
		return std::make_unique<Goblin>();

	case 2:
		return std::make_unique<game::entities::Demon>();

	case 3:
		return std::make_unique<Golem>();

	default:
		return nullptr;
	}
}

//
// === Constructor & Destructor ===
//

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