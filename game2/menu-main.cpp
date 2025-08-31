#include <iostream>
#include "menu-main.h"
#include "menu.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Player.h"
#include "Rec.h"
#include "Font.h"
#include "Graphic.h"
#include "Button.h"

static Button start_btn;
static Button lan_btn;
static Button exit_btn;
static bool once_init = true;

void update_mainmenu() {
	if (once_init) {
		once_init = false;

		start_btn = Button {
			.text = "Start",
			.text_offset_x = 0,
			.text_offset_y = 0,
			.text_size = 60,
			.rectangle = Rectangle{resolutionx / 2, resolutiony / 2, 200, 60},
			.click_sound = "bullet_sound",
			//.texture = "player",
			.action = []{
				next_menu(menu_Type::character_menu);
			}
		};
		lan_btn = Button{
			.text = "Lan",
			.text_offset_x = 0,
			.text_offset_y = 0,
			.text_size = 60,
			.rectangle = Rectangle{resolutionx / 2, resolutiony / 2 + 70, 200, 60},
			.click_sound = "bullet_sound",
			//.texture = "player",
			.action = [] {
				next_menu(menu_Type::lan);
			}
		};
	}

	check(start_btn);
	check(lan_btn);
}

void render_mainmenu(sf::RenderWindow& window) {
	background = "bg_for_menu";
	draw_texture(window, background, resolutionx/2,resolutiony/2, fullscreen ? 2.f : 1.f);
	draw(window, start_btn);
	draw(window, lan_btn);
}
