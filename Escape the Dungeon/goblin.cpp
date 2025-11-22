#include "goblin.h"

#include <string>
#include <vector>

#include "damage_type.h"
#include "defense_profile.h"
#include "player.h"
#include "sword.h"

Goblin::Goblin() :
	Enemy(
		"Goblin", 
		25.0, 
		50, 
		0.10, 
		[]()
		{
			std::vector<DefenseProfile> profiles;

			profiles.push_back({DamageType::Physical, -0.3});

			return profiles;
		}(),
		[]()
		{
			std::vector<std::unique_ptr<Item>> inventory;

			inventory.push_back(std::make_unique<items::Sword>());

			return inventory;
		}()
	)
{ }

std::vector<std::string> Goblin::makeTurn(Player& player)
{
	Item* item = this->getItem("schwert");
	return item->use(*this, player);
}