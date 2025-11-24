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
{ }

//
// === Protected Methods ===
//

HitInfo Spell::dealDamage(Entity& target)
{
	TakeDamageResult result = target.takeDamage(this->damageType_, this->damage_, false);

	return { result.damage, result.multiplier, false, false };
}

std::string Spell::makeDamageEvent(const HitInfo& info, const Entity& target)
{
	std::string event = target.getName() + " erhielt " + utils::ui::format(info.damage, 2) + " Schaden!";

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

void Spell::reduceStamina(Entity& user, std::vector<std::string>& events)
{
	user.consumeStamina(this->staminaCost_);

	events.push_back(user.getName() + " verlor " + std::to_string(this->staminaCost_) + "AP.");
}

std::string Spell::makeStaminaEvent(int lostStamina, const Entity& user)
{
	return user.getName() + " verlor " + std::to_string(this->staminaCost_) + "AP.";
}

std::string Spell::getBasicDescription()
{
	return
		"( Typ: Zauber, Schaden: " + utils::ui::format(this->damage_, 2) + ", Schadenstyp: "
		+ utils::ui::convert(this->damageType_) + ", Kosten: " + std::to_string(this->staminaCost_) + "AP )";

}