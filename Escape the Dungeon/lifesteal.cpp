#include "lifesteal.h"

#include "damage_type.h"
#include "ui_utils.h"
#include "entity.h"

namespace items {
	Lifesteal::Lifesteal() :
		Spell("Lebensraub", 25, 25.0, DamageType::Dark)
	{ }

	std::vector<std::string> Lifesteal::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " wirkt Lebensraub auf " + target.getName() + "..." };

		HitInfo info = this->dealDamage(target);
		events.push_back(this->makeDamageEvent(info, target));

		user.heal(info.damage * 0.5);
		events.push_back(user.getName() + " heilte sich um " + utils::ui::format(info.damage * 0.5, 2) + " LP!");

		user.consumeStamina(this->staminaCost_);
		events.push_back(this->makeStaminaEvent(this->staminaCost_, user));

		return events;
	}
	std::string Lifesteal::getDescription()
	{
		return this->getBasicDescription()
			+ "\nHeilt den Nutzer um 50% des verursachten Schadens.";
	}
}