#include "menu-settings.h"
#include "Game_Core.h"
#include "Rec.h"
#include "Menu.h"
#include "Font.h"

void update_settings() {
	if (mouse_pressed == true)
	{
		Rectangle rec;
		rec.x = 366;
		rec.y = 253;
		rec.max_x = 100;
		rec.max_y = 40;
		if (in_Rectangle(rec, static_cast<int>(mousex), static_cast<int>(mousey)))
			std::exit(0);
		else
			next_menu(menu_Type::basic_menu);
	}
}

void render_settings(sf::RenderWindow& window) {
	drawtxt(window, "Resolution", 363, 232, 60);
	drawtxt(window, "Vertical Sinhronization", 220, 232, 60);
}
