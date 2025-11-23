// game_controller.h
//
// First controller which controlls all other controllers. 
// The very basic game logic is controlled here (starting fights, etc.).

#pragma once

#include "player.h"
#include "battle_controller.h"

namespace core
{
	namespace controllers
	{
		class GameController
		{
		private:
			Player player_;
			core::controllers::BattleController battleController_;

		public:
			explicit GameController();

			void init();
			void start();
		};
	}
}

