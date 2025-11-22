#pragma once

#include <string>
#include <vector>

#include "item_type.h"
#include "damage_type.h"

namespace utils 
{
	namespace ui 
	{
		// Formats a number into a string with given decimals points.
		std::string format(double num, int decimals);

		// Makes all characters in a string lowercase.
		std::string toLowerCase(const std::string& text);

		// Splites text into parts after every space.
		std::vector<std::string> splitBySpace(const std::string& text);

		// Converts an enum to a string.
		std::string convert(ItemType type);
		std::string convert(DamageType type);

		// Waits for user input.
		void wait();

		// Clears the console screen.
		void clear();
	}
}

