#pragma once

#include <string>
#include <vector>

#include "enemy.h"

class Player;

namespace game
{
	namespace entities
	{
		class Demon : public Enemy
		{
		public:
			explicit Demon();

			std::vector<std::string> makeTurn(Player& player) override;
		};
	}
}