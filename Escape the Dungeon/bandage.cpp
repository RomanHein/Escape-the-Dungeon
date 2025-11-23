#include "bandage.h"

#include "ui_utils.h"
#include "entity.h"

namespace items
{
	Bandage::Bandage() :
		Consumable("Bandage")
	{ }

	std::vector<std::string> Bandage::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " benutzt " + this->name_ + "..." };

		user.heal(20);
		events.push_back(user.getName() + " stellt 20 Lebenspunkte wiederher!");

		return events;
	}
	std::string Bandage::getDescription()
	{
		return this->getBasicDescription()
			+ "\nEin Kristall welcher 20 Lebenspunkte wiederherstellen kann.";
	}
}