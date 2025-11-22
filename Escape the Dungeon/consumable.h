#pragma once

#include <string>

#include "item.h"

class Consumable : public Item
{
protected:
	std::string getBasicDescription();

public:
	explicit Consumable(const std::string& name);
};

