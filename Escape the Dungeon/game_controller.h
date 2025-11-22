#pragma once

#include "player.h"
#include "battle_controller.h"

class GameController
{
private:
	Player player_;
	BattleController battleController_;

public:
	explicit GameController();

	void init();
	void start();
};

