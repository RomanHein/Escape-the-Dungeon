#include "health_potion.h"

#include "ui_utils.h"
#include "entity.h"

namespace game
{
	namespace items
	{
		HealthPotion::HealthPotion() :
			Consumable("Heiltrank")
		{
		}

		std::vector<std::string> HealthPotion::use(Entity& user, Entity& target)
		{
			std::vector<std::string> events = { user.getName() + " benutzt " + this->name_ + "..." };

			user.heal(60.0);
			events.push_back(user.getName() + " stellt 60 Lebenspunkte wiederher!");

			return events;
		}
		std::string HealthPotion::getDescription()
		{
			return this->getBasicDescription()
				+ "\nEin mächtiger Trank welcher 60 Lebenspunkte wiederherstellen kann.";
		}
	}
}