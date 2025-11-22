#include "poisoning.h"

#include "damage_type.h"
#include "ui_utils.h"
#include "entity.h"

namespace effects {
	Poisoning::Poisoning() :
		DoT("Vergiftung", 3, 10.0, DamageType::Poison)
	{ }

	std::string Poisoning::activate(Entity& target)
	{
		this->duration_--;
		return this->dealDamage(target);
	}
}