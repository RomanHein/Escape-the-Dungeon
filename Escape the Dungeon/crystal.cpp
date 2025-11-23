#include "crystal.h"

#include "ui_utils.h"
#include "entity.h"

namespace items
{
	Crystal::Crystal() :
		Consumable("Kristall")
	{ }

	std::vector<std::string> Crystal::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " benutzt " + this->name_ + "..." };

		user.restoreStamina(20);
		events.push_back(user.getName() + " stellt 20 Ausdauer wiederher!");

		return events;
	}
	std::string Crystal::getDescription()
	{
		return this->getBasicDescription()
			+ "\nEin Kristall welcher 20 Ausdauerpunkte wiederherstellen kann.";
	}
}