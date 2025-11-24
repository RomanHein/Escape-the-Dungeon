#include "lifesteal.h"

#include "damage_type.h"
#include "ui_utils.h"
#include "entity.h"

namespace items {
	Lifesteal::Lifesteal() :
		Spell("Lebensraub", 25, 10.0, DamageType::Dark)
	{ }

	std::vector<std::string> Lifesteal::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " wirkt Lebensraub auf " + target.getName() + "..." };

		double damage = this->dealDamage(user, target, events);

		user.heal(damage * 0.5);
		events.push_back(user.getName() + " heilte sich um " + utils::ui::format(damage * 0.5, 2) + " LP!");

		user.consumeStamina(this->staminaCost_);
		events.push_back(this->makeStaminaEvent(this->staminaCost_, user));

		return events;
	}
	std::string Lifesteal::getDescription()
	{
		return this->getBasicDescription()
			+ "\nStiehlt 50% des geraubten Lebens eines Gegners.";
	}
}