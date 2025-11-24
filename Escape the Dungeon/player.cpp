#include "player.h"

#include <vector>
#include <memory>
#include <algorithm>

#include "defense_profile.h"
#include "ui_utils.h"
#include "stamina_potion.h"
#include "health_potion.h"
#include "crystal.h"
#include "bandage.h"
#include "dagger.h"
#include "lifesteal.h"
#include "fireball.h"
#include "sword.h"
#include "withered_spear.h"

// === Constructor & Destructor ===

Player::Player() :
	Entity(
		"Spieler", 
		100.0, 
		100, 
		0.10, 
		{}, 
		[]()
		{
			std::vector<std::unique_ptr<Item>> inventory;

			// Consumables
			inventory.push_back(std::make_unique<game::items::HealthPotion>());
			inventory.push_back(std::make_unique<game::items::StaminaPotion>());
			inventory.push_back(std::make_unique<game::items::Crystal>());
			inventory.push_back(std::make_unique<game::items::Crystal>());
			inventory.push_back(std::make_unique<game::items::Bandage>());

			// Weapons
			inventory.push_back(std::make_unique<items::Dagger>());
			inventory.push_back(std::make_unique<items::Sword>());
			inventory.push_back(std::make_unique<game::items::WitheredSpear>());

			// Spells
			inventory.push_back(std::make_unique<items::Lifesteal>());
			inventory.push_back(std::make_unique<items::Fireball>());

			return inventory;
		}()
	)
{ }