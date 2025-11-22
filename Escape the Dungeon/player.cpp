#include "player.h"

#include <vector>
#include <memory>
#include <algorithm>

#include "defense_profile.h"
#include "ui_utils.h"
#include "sword.h"
#include "fireball.h"
#include "stamina_potion.h"
#include "lifesteal.h"

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

			inventory.push_back(std::make_unique<items::Sword>());
			inventory.push_back(std::make_unique<items::Fireball>());
			inventory.push_back(std::make_unique<items::StaminaPotion>());
			inventory.push_back(std::make_unique<items::Lifesteal>());

			return inventory;
		}()
	)
{ }