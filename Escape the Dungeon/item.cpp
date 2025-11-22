#include "item.h"

Item::Item(ItemType itemType, const std::string& name, int staminaCost) :
	itemType_(itemType),
	name_(name),
	staminaCost_(staminaCost)
{ }
Item::~Item() = default;

ItemType Item::getItemType() const { return this->itemType_; }
const std::string& Item::getName() const { return this->name_; }
int Item::getStaminaCost() const { return this->staminaCost_; }
