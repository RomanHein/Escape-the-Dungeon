#include "fireball.h"

#include <memory>

#include "damage_type.h"
#include "entity.h"
#include "burning.h"

namespace game
{
	namespace items {
		Fireball::Fireball() :
			Spell("Feuerball", 50, 20.0, DamageType::Fire)
		{
		}

		std::vector<std::string> Fireball::use(Entity& user, Entity& target)
		{
			std::vector<std::string> events = { user.getName() + " beschwört Feuerball auf " + target.getName() + "..." };

			this->dealDamage(user, target, events);

			target.addEffect(std::make_unique<effects::Burning>());
			events.push_back(target.getName() + " erhielt Verbrennung!");

			user.consumeStamina(this->staminaCost_);
			events.push_back(this->makeStaminaEvent(this->staminaCost_, user));

			return events;
		}
		std::string Fireball::getDescription()
		{
			return this->getBasicDescription()
				+ "\nEin mächtiger Zauber welcher dem Opfer schwere Verbrennungen zufügen kann.";
		}
	}
}