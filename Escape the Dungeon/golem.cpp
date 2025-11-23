#include "golem.h"

#include <string>
#include <vector>

#include "damage_type.h"
#include "defense_profile.h"
#include "player.h"
#include "sword.h"

Golem::Golem() :
	Enemy(
		"Golem",
		100.0,
		100,
		0.0,
		[]()
		{
			std::vector<DefenseProfile> profiles;

			profiles.push_back({ DamageType::Physical, 1.0 });

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

std::vector<std::string> Golem::makeTurn(Player& player)
{
	Item* sword = this->getItem("schwert");

	if (this->canPerform(sword->getStaminaCost()))
	{
		return sword->use(*this, player);
	}
	else
	{
		return { "Golem ist erschöpft..." };
	}
}