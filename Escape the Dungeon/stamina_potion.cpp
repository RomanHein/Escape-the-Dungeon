#include "stamina_potion.h"

#include "ui_utils.h"
#include "entity.h"

namespace items
{
	StaminaPotion::StaminaPotion() :
		Consumable("Ausdauertrank")
	{ }

	std::vector<std::string> StaminaPotion::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " benutzt " + this->name_ + "..." };

		user.restoreStamina(60);
		events.push_back(user.getName() + " stellt 60 Ausdauer wiederher!");

		return events;
	}
	std::string StaminaPotion::getDescription()
	{
		return this->getBasicDescription()
			+ "\nEin mächtiger Trank welcher 60 Ausdauerpunkte wiederherstellen kann.";
	}
}