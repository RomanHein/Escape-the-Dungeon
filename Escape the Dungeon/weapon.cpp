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

void Weapon::dealDamage(Entity& user, Entity& target, std::vector<std::string>& events)
{
	bool critical = core::utils::math::randomUnit() < this->critChance_;
	double damage = this->damage_* (1.0 + critical * this->critDamage_);

	TakeDamageResult result = target.takeDamage(this->damageType_, damage, true);
	std::string multiplierMessage = (result.multiplier == 1.0 ? "" : (result.multiplier > 1.0 ? " (+" + utils::ui::format((result.multiplier - 1.0) * 100, 0) + "% wegen Schwäche)" : " (" + utils::ui::format((result.multiplier - 1.0) * 100, 0) + "% wegen Immunität)"));
	std::string criticalHitMessage = (critical ? " (Kritischer Treffer)" : "");

	if (result.dodged)
	{
		events.push_back(target.getName() + " ist dem Angriff ausgewichen!");
	}
	else
	{
		events.push_back(target.getName() + " nahm " + utils::ui::format(result.damage, 2) + " Schaden!" + multiplierMessage + criticalHitMessage);
	}
}
void Weapon::reduceStamina(Entity& user, std::vector<std::string>& events)
{
	user.consumeStamina(this->staminaCost_);

	events.push_back(user.getName() + " verlor " + std::to_string(this->staminaCost_) + "AP.");
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