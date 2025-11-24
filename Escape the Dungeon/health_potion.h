#pragma once

#include <string>
#include <vector>

#include "consumable.h"

class Entity;

namespace game
{
	namespace items
	{
		class HealthPotion : public Consumable
		{
		public:
			explicit HealthPotion();

			std::vector<std::string> use(Entity& user, Entity& target) override;
			std::string getDescription() override;
		};
	}
}