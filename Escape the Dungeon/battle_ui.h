#pragma once

#include <string>
#include <vector>

class Player;
class Enemy;
class Entity;

namespace services {
	namespace battle_ui
	{
		void showBattleMenu(Player& player, Enemy& enemy);
		void printCombatEvents(const std::vector<std::string>& events);
	};
}

