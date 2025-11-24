#include "golem.h"

#include <string>
#include <vector>

#include "damage_type.h"
#include "defense_profile.h"
#include "player.h"
#include "golem_fist.h"

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
			profiles.push_back({ DamageType::Wither, -1.5 });

			return profiles;
		}(),
		[]()
		{
			std::vector<std::unique_ptr<Item>> inventory;

			inventory.push_back(std::make_unique<game::items::GolemFist>());

			return inventory;
		}()
	)
{ }

std::vector<std::string> Golem::makeTurn(Player& player)
{
	Item* golemFist = this->getItem("golem-faust");

	if (this->canPerform(golemFist->getStaminaCost()))
	{
		return golemFist->use(*this, player);
	}
	else
	{
		return { "Golem ist erschöpft..." };
	}
}