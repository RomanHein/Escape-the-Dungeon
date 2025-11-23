#include "game_controller.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "main_ui_service.h"

namespace core
{
	namespace controllers
	{
		//
		// === Constructor & Destructor ===
		//

		GameController::GameController() :
			battleController_(this->player_)
		{}

		//
		// === Public Methods ===
		//

		void GameController::init()
		{
			std::srand(static_cast<unsigned int>(std::time(0)));
			std::locale::global(std::locale("DE_de"));
		}
		void GameController::start()
		{
			core::services::main_ui::showGameIntro();

			for (int i = 0; i < 3; i++)
			{
				bool hasWon = this->battleController_.startBattle();

				if (!hasWon)
				{
					core::services::main_ui::showDefeatScreen();
					return;
				}
			}

			core::services::main_ui::showVictoryScreen();
		}
	}
}