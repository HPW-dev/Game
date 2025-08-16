#include "menu-yesno.h"
#include "Game_Core.h"
#include "Rec.h"
#include "Menu.h"
#include "Font.h"

void update_yes_or_no() {
	if (mouse_pressed) {
		Rectangle rec;
		rec.x = resolutionx / 2 - 0;
		rec.y = resolutiony / 2 - 170 + 120;
		rec.max_x = 100;
		rec.max_y = 60;
		if (in_Rectangle(rec, static_cast<int>(mousex), static_cast<int>(mousey)))
			std::exit(0);
		else
			next_menu(menu_Type::basic_menu);
	}
}

void render_yes_or_no(sf::RenderWindow& window) {
	auto exit_game_y = resolutiony / 2.f - 170.f;
	drawtxt(window, "Exit game?", resolutionx / 2.f - 220, exit_game_y, 90);
	drawtxt(window, "No", resolutionx / 2.f - 200, exit_game_y + 120.f, 60);
	drawtxt(window, "Yes", resolutionx / 2.f - 0, exit_game_y + 120.f, 60);
}
