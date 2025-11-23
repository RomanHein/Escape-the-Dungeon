#pragma once

#include <string>
#include <vector>

#include "item_type.h"
#include "damage_type.h"

namespace utils 
{
	namespace ui 
	{
		// Splites text into parts after every space.
		std::vector<std::string> splitBySpace(const std::string& text);
		// Formats a number into a string with given decimals points.
		std::string format(double num, int decimals);
		// Makes all characters in a string lowercase.
		std::string toLowerCase(const std::string& text);
		// Centers given text between characters.
		std::string centerText(const std::string& text, int width, char filler);
		// Converts an enum to a string.
		std::string convert(ItemType type);
		// Converts an enum to a string.
		std::string convert(DamageType type);
		// Waits for user input.
		void wait();

		// Clears the console screen.
		void clear();
	}
}

