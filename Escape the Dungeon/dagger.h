#pragma once

#include <string>
#include <vector>

#include "weapon.h"

class Entity;

namespace items
{
	class Dagger : public Weapon
	{
	public:
		explicit Dagger();

		std::vector<std::string> use(Entity& user, Entity& target) override;
		std::string getDescription() override;
	};
}