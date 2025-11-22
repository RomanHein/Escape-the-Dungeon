#include "stamina_potion.h"

#include "ui_utils.h"
#include "entity.h"

const double RESTORE_AMOUNT = 0.40;

namespace items
{
	StaminaPotion::StaminaPotion() :
		Consumable("Ausdauertrank")
	{ }

	std::vector<std::string> StaminaPotion::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " benutzt " + this->name_ + "..." };

		user.restoreStamina(static_cast<int>(user.getMaxStamina() * RESTORE_AMOUNT));
		events.push_back(user.getName() + " stellt " + utils::ui::format(RESTORE_AMOUNT * 100, 0) + "% Ausdauer wiederher!");

		return events;
	}
	std::string StaminaPotion::getDescription()
	{
		return this->getBasicDescription()
			+ "\nStellt 40% der Ausdauer wiederher.";
	}
}