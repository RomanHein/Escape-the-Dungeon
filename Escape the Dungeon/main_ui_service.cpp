#include "main_ui_service.h"

#include <iostream>

#include "ui_utils.h"

namespace core
{
	namespace services
	{
		void main_ui::showGameIntro()
		{
			std::cout << utils::ui::centerText("[ Escape The Dungeon ]", 60, '-') << "\n";

			std::cout << "Du bist ein Abenteurer welcher zusammen mit einem Team, tief in einen Dungeon vorgestoßen ist,\n";
			std::cout << "um einen mächtigen Gegner zu besiegen. Euch gelang es mit schweren Verlusten das Monster zu besiegen.\n";
			std::cout << "Du bist der einzige Überlebende, der sich nun ganz allein im Herzen des Dungeons befindet...\n\n";

			utils::ui::wait();

			std::cout << "\nWährend du nach Atem ringst, bemerkst du Schritte, Kratzer und Geflüstere.\n";
			std::cout << "Weitere Kreaturen kommen plötzlich aus ihren Verstecken heraus. Sie haben gewartet. Auf diesen Moment.\n";
			std::cout << "Du ergreifst dein Schwert und mit letzter Kraft, gelingt es dir den Hinterhalt abzuwehren.\n";
			std::cout << "Vor dir erstreckt sich ein langer Gang der durch mehrere Räume nach oben führt, zu deiner Freiheit...\n\n";

			utils::ui::wait();

			std::cout << "\nDu nimmst die Waffen und Gegenstände deiner gefallenen Kameraden an dich, dein einziges Erbe.\n";
			std::cout << "Nutze deine begrenzten Ressourcen. Überlege jeden Zug, denn es könnte dein letzter sein.\n";
			std::cout << "Überlebe... und entkomme aus diesem verfluchten Ort.\n\n";

			utils::ui::wait();
		}

		void main_ui::showDefeatScreen()
		{
			utils::ui::clear();

			std::cout << utils::ui::centerText("[ Game Over ]", 60, '-') << "\n";
			std::cout << "Mit all deiner Kraft hast du gekämpft, aber es reichte nicht.\n";
			std::cout << "Du wurdest vom Gegner hingerichtet. Du hast tapfer gekämpft.\n\n";

			utils::ui::wait();
		}

		void main_ui::showVictoryScreen()
		{
			utils::ui::clear();

			std::cout << utils::ui::centerText("[ Victory ]", 60, '-') << "\n";
			std::cout << "Du ziehst dein Schwert aus dem Körper des Gegners. Du hast es geschafft...\n";
			std::cout << "Mit allen Kräften ist es dir gelungen als einziger zurück an die Oberfläche anzukommen...\n\n";

			utils::ui::wait();
		}
	}
}