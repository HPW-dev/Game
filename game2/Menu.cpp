#include <functional>
#include "Game_Core.h"
#include "Objects.h"
#include "Items.h"
#include "Menu.h"
#include "menu-game.h"
#include "menu-shop.h"
#include "menu-settings.h"
#include "menu-main.h"
#include "menu-yesno.h"

static std::vector <menu_Type> history_of_menu;
static std::function<void()>update_menu_func = {};
static std::function<void(sf::RenderWindow&)> render_menu_func = {};

void next_menu(menu_Type menu) {
	history_of_menu.push_back(menu);
}

void back() {
	history_of_menu.pop_back();
	shop = false;
	shop_items.clear();

	for (auto& button : objects) {
		if (button.type == Type::button) {
			button.hp = 0;
			button.dead_function = {};
		}
	}
}

void update_menu() {
	// проверить что ESC нажали, а потом отпустили
	static bool prev_key = false;
	bool key_esc = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape);
	if (key_esc == true) {
		prev_key = true;
	}
	else if (prev_key == true) {
		prev_key = false;
		back();
	}

	// проверка что меню закончились
	if (history_of_menu.empty()) {
		next_menu(menu_Type::yes_no);
		return;
	}

	auto menu = history_of_menu.back();
	switch (menu)
	{
	case menu_Type::basic_menu:
		update_menu_func = &update_mainmenu;
		render_menu_func = &render_mainmenu;
		break;

	case menu_Type::game_scene:
		update_menu_func = &update_game_scene;
		render_menu_func = &render_game_scene;
		break;

	case menu_Type::yes_no:
		update_menu_func = &update_yes_or_no;
		render_menu_func = &render_yes_or_no;
		break;

	default: break;
	case menu_Type::shop:
		update_menu_func = &update_shop;
		render_menu_func = &render_shop;
		break;
	}

	assert(update_menu_func);
	update_menu_func();
}

void menu_render(sf::RenderWindow& window) {
	assert(render_menu_func);
	render_menu_func(window);
}
