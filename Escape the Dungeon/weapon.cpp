#include "weapon.h"

#include "item_type.h"
#include "take_damage_result.h"
#include "ui_utils.h"
#include "math_utils.h"
#include "entity.h"

//
// === Constructor & Destructor ===
//

Weapon::Weapon(
	const std::string name, 
	int staminaCost, 
	double damage, 
	DamageType damageType, 
	double critChance, 
	double critDamage,
	double hitChance
) :
	Item(ItemType::Weapon, name, staminaCost),
	damage_(damage),
	damageType_(damageType),
	critChance_(critChance),
	critDamage_(critDamage),
	hitChance_(hitChance)
{ }

//
// === Protected Methods ===
//

HitInfo Weapon::dealDamage(Entity& target)
{
	if (core::utils::math::randomUnit() < target.getDodgeChance() || core::utils::math::randomUnit() > this->hitChance_)
	{
		return { 0.0, 1.0, false, true };
	}

	bool critical = core::utils::math::randomUnit() < this->critChance_;
	double damage = this->damage_* (1.0 + critical * this->critDamage_);

	TakeDamageResult result = target.takeDamage(this->damageType_, damage, false);

	return { result.damage, result.multiplier, critical, false };
}
std::string Weapon::makeDamageEvent(const HitInfo& info, const Entity& target)
{
	if (info.dodged)
	{
		return target.getName() + " ist dem Angriff ausgewichen!";
	}

	std::string event = target.getName() + " nahm " + utils::ui::format(info.damage, 2) + " Schaden!";

	if (info.damageMultiplier > 1.0)
	{
		event += " (+" + utils::ui::format((info.damageMultiplier - 1.0) * 100, 0) + "% wegen Schwäche)";
	}
	else if (info.damageMultiplier < 1.0)
	{
		event += " (" + utils::ui::format((info.damageMultiplier - 1.0) * 100, 0) + "% wegen Immunität)";
	}

	if (info.criticalHit)
	{
		event += " (Kritischer Treffer)";
	}

	return event;
}
std::string Weapon::makeStaminaEvent(Entity& user, int lostStamina)
{
	return user.getName() + " verlor " + std::to_string(this->staminaCost_) + "AP.";
}
std::string Weapon::getBasicDescription()
{
	return
		"( Typ: Waffe, Schaden: " + utils::ui::format(this->damage_, 2) + ", Schadenstyp: "
		+ utils::ui::convert(this->damageType_) + ", Kosten: " + std::to_string(this->staminaCost_) + "AP, CR: " 
		+ utils::ui::format(this->critChance_ * 100, 0) + "% CD: " + utils::ui::format(this->critDamage_ * 100, 0) + "% )";
}

//
// === Getters & Setters ===
//

double Weapon::getDamage() const { return this->damage_; }
DamageType Weapon::getDamageType() const { return this->damageType_; }
double Weapon::getCritChance() const { return this->critChance_; }
double Weapon::getCritDamage() const { return this->critDamage_; }