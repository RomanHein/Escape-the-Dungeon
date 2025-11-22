#pragma once

#include <string>

#include "enemy.h"

class Player;

class Goblin : public Enemy
{
public:
	explicit Goblin();

	std::vector<std::string> makeTurn(Player& player) override;
};

