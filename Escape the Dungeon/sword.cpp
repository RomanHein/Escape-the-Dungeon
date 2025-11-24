#include "sword.h"

#include "damage_type.h"
#include "ui_utils.h"
#include "entity.h"

namespace items {
	Sword::Sword() :
		Weapon("Schwert", 10, 15.0, DamageType::Physical, 0.15, 0.50, 0.9)
	{ }

	std::vector<std::string> Sword::use(Entity& user, Entity& target)
	{
		std::vector<std::string> events = { user.getName() + " greift " + target.getName() + " an..."};

		this->dealDamage(user, target, events);
		this->reduceStamina(user, events);

		return events;
	}
	std::string Sword::getDescription()
	{
		return this->getBasicDescription()
			+ "\nVerfügt über keine besonderen Fähigkeiten. Besitzt aber über hohen Basis-Schaden.";
	}
}