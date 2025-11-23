#include "battle_controller.h"

#include <iostream>

#include "ui_utils.h"
#include "enemy.h"
#include "player.h"
#include "poisoning.h"
#include "battle_ui_service.h"
#include "command_executor.h"

namespace core
{
	namespace controllers
	{
		//
		// === Constructor & Destructor ===
		//

		BattleController::BattleController(Player& player) :
			player_(player),
			enemy_(nullptr),
			turn_(0)
		{
		}
		BattleController::~BattleController() = default;

		//
		// === Private Methods ===
		//

		std::vector<std::string> BattleController::handlePlayerTurn()
		{
			std::vector<std::string> events;
			std::vector<std::string> tokens;

			while (true)
			{
				tokens = core::services::command_executor::getCommandLine();
				events = core::services::command_executor::executeCommand(tokens, this->player_, *this->enemy_);

				// Player gave a combat-based commmand, we can proceed.
				if (!events.empty())
				{
					return events;
				}
			}
		}

		//
		// === Public Methods ===
		//

		bool BattleController::startBattle()
		{
			std::vector<std::string> events;

			this->enemy_ = Enemy::createRandom();
			this->turn_ = 0;

			while (true)
			{
				core::services::battle_ui::showBattleMenu(this->player_, *this->enemy_);

				// Activate effects.
				events = (this->turn_ % 2 == 0 ? this->player_.processEffects() : this->enemy_->processEffects());
				core::services::battle_ui::printCombatEvents(events);

				// Check if player or enemy died after dot.
				if (!this->player_.isAlive() || !this->enemy_->isAlive())
				{
					std::cout << (this->player_.isAlive() ? "Du hast " + this->enemy_->getName() + " besiegt!\n\n" : "Du wurdest von " + this->enemy_->getName() + " besiegt!\n\n");
					utils::ui::wait();

					return this->player_.isAlive();
				}

				// Force turn.
				events = (this->turn_ % 2 == 0 ? this->handlePlayerTurn() : this->enemy_->makeTurn(this->player_));
				core::services::battle_ui::printCombatEvents(events);

				// Exit if either player or enemy is defeated and return victory result.
				if (!this->player_.isAlive() || !this->enemy_->isAlive())
				{
					std::cout << (this->player_.isAlive() ? "Du hast " + this->enemy_->getName() + " besiegt!\n\n" : "Du wurdest von " + this->enemy_->getName() + " besiegt!\n\n");
					utils::ui::wait();

					return this->player_.isAlive();
				}

				this->turn_++;

				utils::ui::wait();
			}

			return false;
		}
	}
}