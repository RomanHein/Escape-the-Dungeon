#pragma once

#include <string>

class Entity;

class Effect
{
protected:
	std::string name_;
	int duration_;

public:
	explicit Effect(const std::string& name, int duration);
	virtual ~Effect();

	virtual std::string activate(Entity& target) = 0;

	bool isExpired() const;

	const std::string& getName() const;
	int getDuration() const;
};

