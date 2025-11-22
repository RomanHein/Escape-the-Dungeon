#include "consumable.h"

#include "item_type.h"

//
// === Constructor & Destructor ===
//

Consumable::Consumable(const std::string& name) :
	Item(ItemType::Consumable, name, 0)
{ }

//
// === Protected Methods ===
//

std::string Consumable::getBasicDescription()
{
	return "( Typ: Gegenstand )";
}