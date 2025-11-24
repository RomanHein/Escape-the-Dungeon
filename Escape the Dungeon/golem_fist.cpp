#include "golem_fist.h"

#include "damage_type.h"
#include "hit_info.h"
#include "ui_utils.h"
#include "entity.h"

namespace game
{
	namespace items {
		GolemFist::GolemFist() :
			Weapon("Golem-Faust", 10, 30.0, DamageType::Physical, 0.50, 0.50, 0.25)
		{ }

		std::vector<std::string> GolemFist::use(Entity& user, Entity& target)
		{
			std::vector<std::string> events = { user.getName() + " greift " + target.getName() + " an..." };

			HitInfo hitInfo = this->dealDamage(target);
			events.push_back(this->makeDamageEvent(hitInfo, target));

			user.consumeStamina(this->staminaCost_);
			events.push_back(this->makeStaminaEvent(user, this->staminaCost_));

			return events;
		}
		std::string GolemFist::getDescription()
		{
			return this->getBasicDescription()
				+ "\nVerfügt über keine besonderen Fähigkeiten. Besitzt aber über hohen Basis-Schaden.";
		}
	}
}