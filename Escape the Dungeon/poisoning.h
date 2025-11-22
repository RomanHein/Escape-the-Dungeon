#pragma once

#include <string>

#include "dot.h"

class Entity;

namespace effects {
	class Poisoning : public DoT
	{
	public:
		explicit Poisoning();

		std::string activate(Entity& target) override;
	};
}

