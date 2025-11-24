// item.h
//
// Base class for all items in the game.

#pragma once

#include <string>
#include <vector>

#include "item_type.h"

class Entity;

class Item
{
private:
	ItemType itemType_;

protected:
	std::string name_;
	int staminaCost_;

public:
	//
	// === Constructor & Destructor ===
	//

	explicit Item(ItemType itemType, const std::string& name, int staminaCost);
	virtual ~Item();

	//
	// === Public Methods ===
	//

	// Uses the item, returns strings which describe the outcome of the usage.
	virtual std::vector<std::string> use(Entity& user, Entity& target) = 0;

	// Returns a description of the item.
	virtual std::string getDescription() = 0;

	//
	// === Getters & Setters ===
	//

	ItemType getItemType() const;
	const std::string& getName() const;
	int getStaminaCost() const;
};

