// consumable.h
//
// Base class for all consumables in the game. Consumables are items which are removed from an
// entity's inventory after usage.

#pragma once

#include <string>

#include "item.h"

class Consumable : public Item
{
protected:
	//
	// === Protected Methods ===
	//

	// Returns a basic description of the consumable.
	std::string getBasicDescription();

public:
	//
	// === Constructor & Destructor ===
	//

	explicit Consumable(const std::string& name);
};

