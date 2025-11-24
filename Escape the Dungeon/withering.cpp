#include "withering.h"

#include "damage_type.h"
#include "ui_utils.h"
#include "entity.h"

namespace game
{
	namespace effects {
		Withering::Withering() :
			DoT("Verdorrung", 2, 15.0, DamageType::Wither)
		{ }

		std::string Withering::activate(Entity& target)
		{
			this->duration_--;
			return this->dealDamage(target);
		}
	}
}