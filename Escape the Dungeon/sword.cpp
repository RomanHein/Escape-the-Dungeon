#include "sword.h"

#include "damage_type.h"
#include "hit_info.h"
#include "ui_utils.h"
#include "entity.h"

namespace items {
	Sword::Sword() :
		Weapon("Schwert", 10, 15.0, DamageType::Physical, 0.15, 0.50, 0.9)
	{ }

	std::vector<std::string> Sword::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " greift " + target.getName() + " an..."};

		HitInfo hitInfo = this->dealDamage(target);
		events.push_back(this->makeDamageEvent(hitInfo, target));

		user.consumeStamina(this->staminaCost_);
		events.push_back(this->makeStaminaEvent(user, this->staminaCost_));

		return events;
	}
	std::string Sword::getDescription()
	{
		return this->getBasicDescription()
			+ "\nVerfügt über keine besonderen Fähigkeiten. Besitzt aber über hohen Basis-Schaden.";
	}
}