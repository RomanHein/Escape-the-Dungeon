#include "entity.h"

#include <algorithm>

#include "math_utils.h"
#include "ui_utils.h"
#include "effect.h"
#include "item.h"

// === Constructor & Destructor ===

Entity::Entity(
	const std::string& name, 
	double initialHealth, 
	int initialStamina, 
	double dodgeChance, 
	const std::vector<DefenseProfile>& defenseProfile,
	std::vector<std::unique_ptr<Item>>&& inventory
) :
	name_(name),
	health_(initialHealth),
	maxHealth_(initialHealth),
	stamina_(initialStamina),
	maxStamina_(initialStamina),
	dodgeChance_(dodgeChance),
	defenseProfiles_(defenseProfile),
	inventory_(std::move(inventory))
{ }
Entity::~Entity() = default;

// === Public Methods ===

TakeDamageResult Entity::takeDamage(DamageType damageType, double damage, bool dodgeable)
{
	double multiplier = 1.0;

	if (dodgeable && utils::math::randomInt(1, 100) / 100.0 <= this->dodgeChance_)
	{
		return { 0.0, 0.0, true };
	}

	// Increase/Decrease incoming damage depending on whether entity has multiplier for damage type
	for (const auto& profile : this->defenseProfiles_)
	{
		if (profile.damageType == damageType)
		{
			multiplier -= profile.multiplier;
			damage *= multiplier;
			break;
		}
	}

	// Make sure health doesn't fall below 0.
	this->health_ = std::max(this->health_ - damage, 0.0);

	return { damage, multiplier, false };
}
void Entity::heal(double amount)
{
	this->health_ = std::min(this->health_ + amount, this->maxHealth_);
}
void Entity::consumeStamina(int amount)
{
	this->stamina_ = std::max(0, this->stamina_ - amount);
}
void Entity::restoreStamina(int amount)
{
	this->stamina_ = std::min(this->maxStamina_, this->stamina_ + amount);
}
void Entity::addEffect(std::unique_ptr<Effect> effect)
{
	this->effects_.push_back(std::move(effect));
}
std::vector<std::string> Entity::processEffects()
{
	std::vector<std::string> events = { this->name_ + "'s Effekte aktivieren sich..." };

	// Exit if no effects present.
	if (this->effects_.empty())
	{
		events.push_back(this->name_ + " hat keine aktiven Effekte.");
		return events;
	}

	// Activate all effects once and save their reports.
	for (auto& effect : this->effects_)
	{
		events.push_back(effect->activate(*this));
	}

	// Remove expired effects.
	this->effects_.erase(
		std::remove_if(this->effects_.begin(), this->effects_.end(), [](const std::unique_ptr<Effect>& e) { return e->isExpired(); }),
		this->effects_.end()
	);

	return events;
}
Item* Entity::getItem(const std::string& name)
{
	auto it = std::find_if(this->inventory_.begin(), this->inventory_.end(), [&name](const std::unique_ptr<Item>& item)
		{ return utils::ui::toLowerCase(item->getName()) == utils::ui::toLowerCase(name); }
	);

	if (it != this->inventory_.end())
	{
		return it->get();
	}
	else
	{
		return nullptr;
	}
}
void Entity::removeItem(const std::string& name)
{
	auto it = std::find_if(this->inventory_.begin(), this->inventory_.end(), [&name](const std::unique_ptr<Item>& item)
		{ return utils::ui::toLowerCase(item->getName()) == utils::ui::toLowerCase(name); }
	);

	if (it != this->inventory_.end())
	{
		this->inventory_.erase(it);
	}
}

// === Predicate Methods ===

bool Entity::isAlive() const { return this->health_ > 0.0; }
bool Entity::canPerform(int staminaCost) const { return this->stamina_ - staminaCost >= 0; }
bool Entity::hasItem(const std::string& name) const
{
	return std::find_if(this->inventory_.begin(), this->inventory_.end(), [&name](const std::unique_ptr<Item>& item)
		{ return utils::ui::toLowerCase(item->getName()) == utils::ui::toLowerCase(name); }
	) != this->inventory_.end();
}
bool Entity::isWeakTo(DamageType damageType) const
{
	return std::find_if(this->defenseProfiles_.begin(), this->defenseProfiles_.end(), [&damageType](const DefenseProfile& profile)
		{ return profile.damageType == damageType && profile.multiplier < 0.0; }
	) != this->defenseProfiles_.end();
}

// === Getters & Setters ===

const std::string& Entity::getName() const { return this->name_; }
double Entity::getHealth() const { return this->health_; }
double Entity::getMaxHealth() const { return this->maxHealth_; }
int Entity::getStamina() const { return this->stamina_; }
int Entity::getMaxStamina() const { return this->maxStamina_; }
double Entity::getDodgeChance() const { return this->dodgeChance_; }
const std::vector<DefenseProfile>& Entity::getDefenseProfiles() const { return this->defenseProfiles_; }
const std::vector<std::unique_ptr<Item>>& Entity::getInventory() const { return this->inventory_; }
const std::vector<std::unique_ptr<Effect>>& Entity::getEffects() const { return this->effects_; }