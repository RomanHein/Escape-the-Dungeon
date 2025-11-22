#pragma once

#include <memory>
#include <string>
#include <vector>

class Player;
class Enemy;

class BattleController
{
private:
	Player& player_;
	std::unique_ptr<Enemy> enemy_;
	int turn_;

	// Asks player to make a turn.
	std::vector<std::string> handlePlayerTurn();

public:
	explicit BattleController(Player& player);
	~BattleController();

	bool startBattle();
};

