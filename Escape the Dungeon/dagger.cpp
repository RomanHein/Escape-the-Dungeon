#include "dagger.h"

#include "damage_type.h"
#include "hit_info.h"
#include "math_utils.h"
#include "ui_utils.h"
#include "entity.h"

namespace items {
	Dagger::Dagger() :
		Weapon("Dolch", 10, 15.0, DamageType::Physical, 0.15, 0.50, 1.0)
	{ }

	std::vector<std::string> Dagger::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " greift " + target.getName() + " an..." };

		for (int i = 0; i < core::utils::math::randomInt(1, 3); i++)
		{
			HitInfo hitInfo = this->dealDamage(target);
			events.push_back(this->makeDamageEvent(hitInfo, target));
		}

		user.consumeStamina(this->staminaCost_);
		events.push_back(this->makeStaminaEvent(user, this->staminaCost_));

		return events;
	}
	std::string Dagger::getDescription()
	{
		return this->getBasicDescription()
			+ "\nEin leichter Dolch, kann benutzt werden um 1 - 3 Angriffe in Folge zu machen.\n"
			+ "Liegt gut in der Hand und eignet sich ideal für flinke Gegner";
	}
}