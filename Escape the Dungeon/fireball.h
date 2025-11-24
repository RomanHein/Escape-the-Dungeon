#pragma once

#include <string>
#include <vector>

#include "spell.h"

class Entity;

namespace game
{
	namespace items
	{
		class Fireball : public Spell
		{
		public:
			explicit Fireball();

			std::vector<std::string> use(Entity& user, Entity& target) override;
			std::string getDescription() override;
		};
	}
}

