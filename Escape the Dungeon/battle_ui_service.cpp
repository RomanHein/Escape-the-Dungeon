#include "battle_ui_service.h"

#include <iostream>
#include <vector>
#include <string>

#include "ui_utils.h"
#include "player.h"
#include "enemy.h"

//
// === Namespace Functions ===
//

namespace core
{
	namespace services
	{
		void battle_ui::showBattleMenu(Player& player, Enemy& enemy)
		{
			utils::ui::clear();

			std::cout << utils::ui::centerText("[ " + enemy.getName() + " ]", 40, '=') << "\n";
			std::cout << "Lebenspunkte: " << utils::ui::format(enemy.getHealth(), 0) << "/" << utils::ui::format(enemy.getMaxHealth(), 0) << " [" << utils::ui::format(enemy.getHealth() / enemy.getMaxHealth() * 100, 0) << "%]\n";
			std::cout << "Ausdauer: " << utils::ui::format(enemy.getStamina(), 0) << "/" << utils::ui::format(enemy.getMaxStamina(), 0) << "\n\n";

			std::cout << utils::ui::centerText("[ " + player.getName() + " ]", 40, '=') << "\n";
			std::cout << "Lebenspunkte: " << utils::ui::format(player.getHealth(), 0) << "/" << utils::ui::format(player.getMaxHealth(), 0) << " [" << utils::ui::format(player.getHealth() / player.getMaxHealth() * 100, 0) << "%]\n";
			std::cout << "Ausdauer: " << utils::ui::format(player.getStamina(), 0) << "/" << utils::ui::format(player.getMaxStamina(), 0) << "\n\n";

			std::cout << utils::ui::centerText("[ Event Fenster ]", 40, '=') << "\n";
		}
		void battle_ui::printCombatEvents(const std::vector<std::string>& events)
		{
			for (const auto& event : events)
			{
				std::cout << event << "\n";
			}

			std::cout << "\n";
		}
	}
}