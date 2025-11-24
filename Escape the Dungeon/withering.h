#pragma once

#include <string>

#include "dot.h"

class Entity;

namespace game
{
	namespace effects {
		class Withering : public DoT
		{
		public:
			explicit Withering();

			std::string activate(Entity& target) override;
		};
	}
}