#pragma once

#include <string>

class Entity;

class Effect
{
protected:
	std::string name_;
	int duration_;

public:
	//
	// === Constructor & Destructor ===
	//

	explicit Effect(const std::string& name, int duration);
	virtual ~Effect();

	//
	// === Public Methods ===
	//

	// Activates the effect on the target. Returns string which describes the event.
	virtual std::string activate(Entity& target) = 0;

	//
	// === Predicate Methods ===
	//

	// Returns true if the effect's duration is 0.
	bool isExpired() const;

	//
	// === Getters & Setters ===
	//

	const std::string& getName() const;
	int getDuration() const;
};

