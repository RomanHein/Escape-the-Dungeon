#pragma once

#include <string>
#include <vector>

#include "enemy.h"

class Player;

class Demon : public Enemy
{
public:
	explicit Demon();

	std::vector<std::string> makeTurn(Player& player) override;
};

