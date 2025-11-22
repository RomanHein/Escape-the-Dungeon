#include "burning.h"

#include "damage_type.h"
#include "ui_utils.h"
#include "entity.h"

namespace effects {
	Burning::Burning() :
		DoT("Verbrennung", 3, 7.5, DamageType::Fire)
	{ }

	std::string Burning::activate(Entity& target)
	{
		this->duration_--;
		return this->dealDamage(target);
	}
}