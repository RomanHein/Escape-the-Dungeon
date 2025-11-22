#include "effect.h"

#include "take_damage_result.h"

// === Constructor & Destructor ===

Effect::Effect(const std::string& name, int duration) :
	name_(name),
	duration_(duration)
{ }
Effect::~Effect() = default;

// === Predicate Methods ===

bool Effect::isExpired() const { return this->duration_ <= 0; }

// === Getters & Setters ===

const std::string& Effect::getName() const { return this->name_; }
int Effect::getDuration() const { return this->duration_; }