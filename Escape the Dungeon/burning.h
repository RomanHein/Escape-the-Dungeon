#pragma once

#include <string>

#include "dot.h"

class Entity;

namespace effects {
	class Burning : public DoT
	{
	public:
		explicit Burning();

		std::string activate(Entity& target) override;
	};
}

