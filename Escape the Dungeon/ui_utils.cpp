#include "ui_utils.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

//
// === Namespace Functions ===
//

namespace utils
{
	std::string ui::format(double num, int decimals)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(decimals) << num;

		return stream.str();
	}

	std::string ui::toLowerCase(const std::string& text)
	{
		std::string result = text;

		std::transform(result.begin(), result.end(), result.begin(), [](char c) { return std::tolower(c); });

		return result;
	}

	std::vector<std::string> ui::splitBySpace(const std::string& text)
	{
		std::istringstream iss(text);
		std::vector<std::string> parts;
		std::string word;

		// Magic.
		while (iss >> word)
		{
			parts.push_back(word);
		}

		return parts;
	}
	std::string ui::convert(DamageType type)
	{
		switch (type)
		{
		case DamageType::Physical:
			return "Physisch";

		case DamageType::Fire:
			return "Feuer";

		case DamageType::Ice:
			return "Eis";

		case DamageType::Poison:
			return "Gift";

		default:
			return "Unbekannt";
		}
	}
	std::string ui::convert(ItemType type)
	{
		switch (type)
		{
		case ItemType::Weapon:
			return "Waffe";

		default:
			return "Unbekannt";
		}
	}
	std::string ui::centerText(const std::string& text, int width, char filler)
	{
		std::string left = std::string((width - text.length()) / 2, filler);
		std::string right = std::string(width - left.length() - text.length(), filler);

		return left + text + right;
	}
	void ui::wait()
	{
		std::cout << "Drücke Enter um fortzufahren...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	void ui::clear()
	{
		system("cls");
	}
}