#include "command_executor.h"

#include <iostream>
#include <unordered_map>
#include <functional>

#include "command_type.h"
#include "item_type.h"
#include "take_damage_result.h"
#include "defense_profile.h"
#include "ui_utils.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "effect.h"

//
// === Local Variables ===
//

static const std::unordered_map<std::string, CommandType> COMMAND_MAP = {
	{"zeige", CommandType::Show},
	{"help", CommandType::Help},
	{"hilfe", CommandType::Help},
	{"?", CommandType::Help},
	{"benutze", CommandType::Use},
	{"use", CommandType::Use},
	{"wirke", CommandType::Cast},
	{"cast", CommandType::Cast},
	{"beschwöre", CommandType::Cast},
	{"verbrauche", CommandType::Consume}
};

//
// === Local Functions ===
//

// Formats error message.
std::vector<std::string> error(const std::string& message)
{
	std::cerr << "Error: " << message << "\n";
	return {};
}
// Converts string into a valid command.
CommandType convertToCommand(const std::string& input)
{
	auto it = COMMAND_MAP.find(utils::ui::toLowerCase(input));
	return (it != COMMAND_MAP.end() ? it->second : CommandType::Unknown);
}
// Handles 'help'.
std::vector<std::string> handleHelp()
{
	std::cout << "zeige <was> <von>\n";
	std::cout << " <was>: 'waffen' | 'zauber' | 'sachen' | 'verteidigung' | 'effekte'\n";
	std::cout << " <von>: 'gegner' | 'eigene'\n";
	std::cout << "Nutzen: Zeigt Information über eine bestimmte Sache von jemandem.\n";
	std::cout << "Beispiel: 'zeige waffen gegner'.\n\n";

	std::cout << "benutze <waffe>\n";
	std::cout << " <waffe>: Name einer Waffe\n";
	std::cout << "Nutzen: Greift Gegner mit einer Waffe an.\n";
	std::cout << "Beispiel: 'benutze schwert'.\n\n";

	std::cout << "wirke <zauber>\n";
	std::cout << " <zauber>: Name eines Zaubers\n";
	std::cout << "Nutzen: Wirkt einen Zauber auf einen Gegner.\n";
	std::cout << "Beispiel: 'wirke feuerball'.\n\n";

	std::cout << "verbrauche <sache>\n";
	std::cout << " <sache>: Name eines Gegenstandes\n";
	std::cout << "Nutzen: Benutzt und verbraucht einen Gegenstand.\n";
	std::cout << "Beispiel: 'verbrauche ausdauertrank'.\n";

	return {};
}
// Handles 'zeige <was> <von>'.
std::vector<std::string> handleShow(const std::vector<std::string>& tokens, Player& player, Enemy& enemy)
{
	// Missing param.
	if (tokens.size() < 2)
	{
		return error("Fehlender Parameter: '<was>'. \nAnwendung: zeige <was> <von>.");
	}

	std::string what = utils::ui::toLowerCase(tokens[1]);

	// Invalid param.
	if (what != "waffen" && what != "verteidigung" && what != "effekte" && what != "zauber" && what != "sachen")
	{
		return error("Ungültiger Parameter: '" + what + "'. \n<was> ist 'waffen' oder 'verteidigung', 'zauber', 'sachen' oder 'effekte'.");
	}

	// Missing param.
	if (tokens.size() < 3)
	{
		return error("Fehlender Parameter: '<von>'. \nAnwendung: zeige <was> <von>.");
	}

	std::string who = utils::ui::toLowerCase(tokens[2]);

	// Invalid param.
	if (who != "gegner" && who != "eigene")
	{
		return error("Ungültiger Parameter: '" + who + "'. \n<von> ist 'gegner' oder 'eigene'.");
	}

	// Weapons, Spells and Items.
	if (what == "waffen" || what == "zauber" || what == "sachen")
	{
		for (const auto& item : (who == "gegner" ? enemy.getInventory() : player.getInventory()))
		{
			if (item->getItemType() != (what == "waffen" ? ItemType::Weapon : (what == "zauber" ? ItemType::Spell : ItemType::Consumable)))
			{
				continue;
			}

			std::cout << item->getName() << " " << item->getDescription() << "\n";
		}
	}
	// Defense Profiles.
	else if (what == "verteidigung")
	{
		for (const auto& profile : (who == "gegner" ? enemy.getDefenseProfiles() : player.getDefenseProfiles()))
		{
			std::cout << utils::ui::convert(profile.damageType) << ": " << (profile.multiplier < 0.0 ? "+" : "") << utils::ui::format(-profile.multiplier * 100, 0) << "% Schaden\n";
		}
	}
	// Effects.
	else if (what == "effekte")
	{
		for (const auto& effect : (who == "gegner" ? enemy.getEffects() : player.getEffects()))
		{
			std::cout << effect->getName() << "\n";
		}
	}

	return {};
}
// Handles 'benutze <waffe>'.
std::vector<std::string> handleUse(const std::vector<std::string>& tokens, Player& player, Enemy& enemy)
{
	// Missing param.
	if (tokens.size() < 2)
	{
		return error("Fehlender Parameter: '<waffe>'. \nBenutzung: 'benutze <waffe>'.");
	}

	std::string weapon = utils::ui::toLowerCase(tokens[1]);

	// Doesn't own spell.
	if (!player.hasItem(weapon))
	{
		return error("'" + weapon + "' nicht im Inventar. \nTipp: benutze 'zeige waffen eigene'.");
	}

	Item* item = player.getItem(weapon);

	// Spell isn't spell.
	if (item->getItemType() != ItemType::Weapon)
	{
		return error(weapon + " ist keine Waffe. \nTipp: benutze 'zeige waffen eigene'.");
	}

	// Insufficient stamina.
	if (!player.canPerform(item->getStaminaCost()))
	{
		return error("Ungenügend Ausdauer!");
	}

	return item->use(player, enemy);
}
// Handles 'wirke <zauber>'.
std::vector<std::string> handleCast(const std::vector<std::string>& tokens, Player& player, Enemy& enemy)
{
	// Missing param.
	if (tokens.size() < 2)
	{
		return error("Fehlender Parameter: '<zauber>'. \nBenutzung: 'wirke <zauber>'.");
	}

	std::string spell = utils::ui::toLowerCase(tokens[1]);

	// Doesn't own spell.
	if (!player.hasItem(spell))
	{
		return error("'" + spell + "' nicht im Inventar. \nTipp: benutze 'zeige zauber eigene'.");
	}

	Item* item = player.getItem(spell);

	// Spell isn't spell.
	if (item->getItemType() != ItemType::Spell)
	{
		return error(spell + " ist kein Zauber. \nTipp: benutze 'zeige zauber eigene'.");
	}

	// Insufficient stamina.
	if (!player.canPerform(item->getStaminaCost()))
	{
		return error("Ungenügend Ausdauer!");
	}

	return item->use(player, enemy);
}
// Handles 'verbrauche <gegenstand>'.
std::vector<std::string> handleConsume(const std::vector<std::string>& tokens, Player& player, Enemy& enemy)
{
	// Missing param.
	if (tokens.size() < 2)
	{
		return error("Fehlender Parameter: '<gegenstand>'. \nBenutzung: 'verbrauche <sache>'.");
	}

	std::string consumable = utils::ui::toLowerCase(tokens[1]);

	// Doesn't own consumable.
	if (!player.hasItem(consumable))
	{
		return error("'" + consumable + "' nicht im Inventar. \nTipp: benutze 'zeige sachen eigene'.");
	}

	Item* item = player.getItem(consumable);

	// Consumable isn't consumable.
	if (item->getItemType() != ItemType::Consumable)
	{
		return error(consumable + " ist kein verbrauchbarer Gegenstand. \nTipp: benutze 'zeige sachen eigene'.");
	}

	// First use, then remove in order to prevent dangling pointer.
	auto events = item->use(player, enemy);
	player.removeItem(consumable);

	return events;
}

//
// === Namespace Functions ===
//

namespace services {
	std::vector<std::string> command_executor::getCommandLine()
	{
		std::vector<std::string> tokens;
		std::string input;

		while (true)
		{
			std::cout << "> ";
			std::getline(std::cin, input);

			tokens = utils::ui::splitBySpace(input);

			if (!tokens.empty())
			{
				return tokens;
			}
		}
	}
	std::vector<std::string> command_executor::executeCommand(const std::vector<std::string>& tokens, Player& player, Enemy& enemy)
	{
		CommandType cmd = convertToCommand(tokens[0]);

		switch (cmd)
		{
		case CommandType::Help:
			return handleHelp();

		case CommandType::Show:
			return handleShow(tokens, player, enemy);

		case CommandType::Use:
			return handleUse(tokens, player, enemy);

		case CommandType::Cast:
			return handleCast(tokens, player, enemy);

		case CommandType::Consume:
			return handleConsume(tokens, player, enemy);

		default:
			return error("Unbekannter Befehl: '" + tokens[0] + "'. \nTipp: benutze 'help'.");
		}
	}
}