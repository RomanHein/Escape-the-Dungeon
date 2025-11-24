#include "spell.h"

#include "item_type.h"
#include "take_damage_result.h"
#include "ui_utils.h"
#include "entity.h"

// === Constructor & Destructor ===

Spell::Spell(const std::string& name, int staminaCost, double damage, DamageType damageType) :
	Item(ItemType::Spell, name, staminaCost),
	damage_(damage),
	damageType_(damageType)
{
}

//
// === Protected Methods ===
//

double Spell::dealDamage(Entity& user, Entity& target, std::vector<std::string>& events)
{
	TakeDamageResult result	= target.takeDamage(this->damageType_, this->damage_, false);
	std::string multiplierMessage = (result.multiplier == 1.0 ? "" : (result.multiplier > 1.0 ? " (+" + utils::ui::format((result.multiplier - 1.0) * 100, 0) + "% wegen Schwäche)" : " (" + utils::ui::format((result.multiplier - 1.0) * 100, 0) + "% wegen Immunität)"));

	if (result.damage != 0.0)
	{
		events.push_back(target.getName() + " erhielt " + utils::ui::format(result.damage, 2) + " Schaden!" + multiplierMessage);
	}

	return result.damage;
}
void Spell::reduceStamina(Entity& user, std::vector<std::string>& events)
{
	user.consumeStamina(this->staminaCost_);

	events.push_back(user.getName() + " verlor " + std::to_string(this->staminaCost_) + "AP.");
}
std::string Spell::getBasicDescription()
{
	return
		"( Typ: Zauber, Schaden: " + utils::ui::format(this->damage_, 2) + ", Schadenstyp: "
		+ utils::ui::convert(this->damageType_) + ", Kosten: " + std::to_string(this->staminaCost_) + "AP )";

}