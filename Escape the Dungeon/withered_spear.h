#pragma once

#include <string>
#include <vector>

#include "weapon.h"

class Entity;

namespace game
{
	namespace items
	{
		class WitheredSpear : public Weapon
		{
		public:
			explicit WitheredSpear();

			std::vector<std::string> use(Entity& user, Entity& target) override;
			std::string getDescription() override;
		};
	}
}