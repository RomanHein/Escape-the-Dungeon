#pragma once

#include <string>
#include <vector>

#include "enemy.h"

class Player;

class Golem : public Enemy
{
public:
	explicit Golem();

	std::vector<std::string> makeTurn(Player& player) override;
};

