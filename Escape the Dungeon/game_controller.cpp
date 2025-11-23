#include "game_controller.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "main_menu_ui_service.h"

//
// === Constructor & Destructor ===
//

GameController::GameController() :
	battleController_(this->player_)
{ }

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
	services::main_menu_ui::showGameIntro();

	for (int i = 0; i < 3; i++)
	{
		bool hasWon = this->battleController_.startBattle();

		if (!hasWon)
		{
			std::cout << "hast verloren :(";
			break;
		}
	}
}