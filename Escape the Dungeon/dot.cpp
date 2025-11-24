#include "dot.h"

#include "take_damage_result.h"
#include "ui_utils.h"
#include "entity.h"

DoT::DoT(const std::string& name, int duration, double damage, DamageType damageType) :
	Effect(name, duration),
	damage_(damage),
	damageType_(damageType)
{ }

std::string DoT::dealDamage(Entity& target)
{
	TakeDamageResult result = target.takeDamage(this->damageType_, this->damage_, false);
	std::string multiplierMessage = (result.multiplier == 1.0 ? "" : (result.multiplier > 1.0 ? " (+" + utils::ui::format((result.multiplier - 1.0) * 100, 0) + "% wegen Schwäche)" : " (" + utils::ui::format((result.multiplier - 1.0) * 100, 0) + "% wegen Resistenz)"));

	return target.getName() + " erhielt " + utils::ui::format(result.damage, 2) + " Schaden wegen " + this->name_ + "!" + multiplierMessage + " (" + std::to_string(this->duration_) + " Ticks übrig)";
}

double DoT::getDamage() const { return this->damage_; }
DamageType DoT::getDamageType() const { return this->damageType_; }