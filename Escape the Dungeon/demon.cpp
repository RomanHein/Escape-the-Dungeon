#include "demon.h"

#include <string>
#include <vector>

#include "damage_type.h"
#include "defense_profile.h"
#include "player.h"
#include "fireball.h"
#include "crystal.h"

Demon::Demon() :
	Enemy(
		"Dämon",
		25.0,
		200,
		0.25,
		[]()
		{
			std::vector<DefenseProfile> profiles;

			profiles.push_back({ DamageType::Fire, 0.35 });
			profiles.push_back({ DamageType::Dark, -0.1 });

			return profiles;
		}(),
		[]()
		{
			std::vector<std::unique_ptr<Item>> inventory;

			inventory.push_back(std::make_unique<items::Fireball>());
			inventory.push_back(std::make_unique<items::Crystal>());
			inventory.push_back(std::make_unique<items::Crystal>());

			return inventory;
		}()
	)
{
}

std::vector<std::string> Demon::makeTurn(Player& player)
{
	Item* fireball = this->getItem("feuerball");

	if (static_cast<double>(this->getStamina()) / this->getMaxStamina() < 0.5 && this->hasItem("kristall"))
	{
		Item* crystal = this->getItem("kristall");

		auto events = crystal->use(*this, player);
		this->removeItem("kristall");

		return events;
	}
	else if (this->canPerform(fireball->getStaminaCost()))
	{
		return fireball->use(*this, player);
	}
	else
	{
		return { "Dämon ist erschöpft..." };
	}
}