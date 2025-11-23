#pragma once

#include <string>
#include <vector>

class Player;
class Enemy;

namespace core
{
	namespace services 
	{
		namespace command_executor
		{
			// Asks player for command, returns tokens.
			std::vector<std::string> getCommandLine();
			// Executes player's command tokens.
			std::vector<std::string> executeCommand(const std::vector<std::string>& tokens, Player& player, Enemy& enemy);
		};
	}
}

