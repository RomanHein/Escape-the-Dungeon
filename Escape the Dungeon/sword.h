#pragma once

#include <string>
#include <vector>

#include "weapon.h"

class Entity;

namespace items 
{
	class Sword : public Weapon
	{
	public:
		explicit Sword();

		std::vector<std::string> use(Entity& user, Entity& target) override;
		std::string getDescription() override;
	};
}