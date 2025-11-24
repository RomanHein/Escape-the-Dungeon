#include "withered_spear.h"

#include <memory>

#include "damage_type.h"
#include "hit_info.h"
#include "ui_utils.h"
#include "math_utils.h"
#include "entity.h"
#include "withering.h"

namespace game
{
	namespace items {
		WitheredSpear::WitheredSpear() :
			Weapon("Speer", 15, 5.0, DamageType::Physical, 0.35, 0.40, 0.75)
		{
		}

		std::vector<std::string> WitheredSpear::use(Entity& user, Entity& target)
		{
			std::vector<std::string> events = { user.getName() + " greift " + target.getName() + " an..." };

			HitInfo hitInfo = this->dealDamage(target);
			events.push_back(this->makeDamageEvent(hitInfo, target));

			if (!hitInfo.dodged && core::utils::math::randomUnit() < 0.5)
			{
				target.addEffect(std::make_unique<game::effects::Withering>());
				events.push_back(target.getName() + " bekam Verdorrung!");
			}

			user.consumeStamina(this->staminaCost_);
			events.push_back(this->makeStaminaEvent(user, this->staminaCost_));

			return events;
		}
		std::string WitheredSpear::getDescription()
		{
			return this->getBasicDescription()
				+ "\nEin Speer der aus unbekanntem Material ist. Pechschwarz, hat eine 50% Chance\n"
				+ "den Gegner Veroddorung zuzufügen.";
		}
	}
}