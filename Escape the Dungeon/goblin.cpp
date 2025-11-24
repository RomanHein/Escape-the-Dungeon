#include "goblin.h"

#include <string>
#include <vector>

#include "damage_type.h"
#include "defense_profile.h"
#include "player.h"
#include "sword.h"
#include "bandage.h"

Goblin::Goblin() :
	Enemy(
		"Goblin", 
		50.0, 
		50, 
		0.15, 
		[]()
		{
			std::vector<DefenseProfile> profiles;

			profiles.push_back({DamageType::Fire, -0.5});

			return profiles;
		}(),
		[]()
		{
			std::vector<std::unique_ptr<Item>> inventory;

			inventory.push_back(std::make_unique<items::Sword>());
			inventory.push_back(std::make_unique<game::items::Bandage>());

			return inventory;
		}()
	)
{ }

std::vector<std::string> Goblin::makeTurn(Player& player)
{
	Item* sword = this->getItem("schwert");

	if (this->getHealth() / this->getMaxHealth() <= 0.5 && this->hasItem("bandage"))
	{
		Item* bandage = this->getItem("bandage");

		auto events = bandage->use(*this, player);
		this->removeItem("bandage");

		return events;
	}
	else if (this->canPerform(sword->getStaminaCost()))
	{
		return sword->use(*this, player);
	}
	else
	{
		return { "Goblin ist erschöpft..." };
	}
}