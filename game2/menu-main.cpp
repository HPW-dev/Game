#include "menu-main.h"
#include "menu.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Player.h"
#include "Rec.h"
#include "Font.h"
#include "Graphic.h"

// сброс игры
static void game_reset() {
	next_menu(menu_Type::game_scene);
	objects.clear();
	difficulty = 1;
	difficulty_max = difficulty_max_default;
	money = 0;
	makeplayer();
}

void update_mainmenu() {
	if (mouse_pressed == true)
	{
		Rectangle rec;
		rec.x = resolutionx / 2;
		rec.y = resolutiony / 2;
		rec.max_x = 200;
		rec.max_y = 60;
		if (in_Rectangle(rec, static_cast<int>(mousex), static_cast<int>(mousey))) {
			game_reset();
		}
	}
}

void render_mainmenu(sf::RenderWindow& window) {
	background = "bg_for_menu";
	draw_texture(window, background, resolutionx/2,resolutiony/2, fullscreen ? 2.f : 1.f);
	drawtxt(window, "Start", resolutionx / 2.f, resolutiony / 2.f, 60);
}
