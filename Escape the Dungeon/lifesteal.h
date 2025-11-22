#pragma once

#include <string>
#include <vector>

#include "spell.h"

class Entity;

namespace items
{
	class Lifesteal : public Spell
	{
	public:
		explicit Lifesteal();

		std::vector<std::string> use(Entity& user, Entity& target) override;
		std::string getDescription() override;
	};
}

