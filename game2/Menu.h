#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Font.h"
#include <vector>
#include "Misc.h"
#include "Game_Core.h"
#include "Game_Object.h"
#include "Player.h"
#include "Bot1.h"
#include <iostream>
#include "Rec.h"
#include "Game_object_control.h"
#include "Items.h"
#include "dps-numbers.h"
#include "Graphic.h"

enum class menu_Type {
	basic_menu,
	game_scene,
	settings,
	yes_no,
	results,
	shop,
};
std::vector <menu_Type> history_of_menu;

void next_menu(menu_Type menu) {
	history_of_menu.push_back(menu);
}

void back() {
	history_of_menu.pop_back();
	shop = false;
	shop_items.clear();

	for (auto& button: objects) {
		if (button.type == Type::button) {
			button.hp = 0;
			button.dead_function = {};
		}
	}
}

void update_yes_or_no() {
	if (mouse_pressed) {
		Rectangle rec;
		rec.x = resolutionx/2 - 0;
		rec.y = resolutiony/2 - 170 + 120;
		rec.max_x = 100;
		rec.max_y = 60;
		if (in_Rectangle(rec, mousex, mousey))
			std::exit(0);
		else
			next_menu(menu_Type::basic_menu);
	}
}

void render_yes_or_no(sf::RenderWindow& window) {
	auto exit_game_y = resolutiony/2 - 170;
	drawtxt(window, "Exit game?", resolutionx/2 - 220, exit_game_y, 90);
	drawtxt(window, "No", resolutionx/2 - 200, exit_game_y + 120, 60);
	drawtxt(window, "Yes", resolutionx/2 - 0, exit_game_y + 120, 60);
	
}

void update_mainmenu() {
	if (mouse_pressed == true)
	{
		Rectangle rec;
		rec.x = resolutionx / 2;
		rec.y = resolutiony / 2;
		rec.max_x = 100;
		rec.max_y = 40;
		if (in_Rectangle(rec, mousex, mousey)) {
			next_menu(menu_Type::game_scene);
			objects.clear();
			difficulty = 0;
			makeplayer();
		}
	}
}

void render_mainmenu(sf::RenderWindow& window) {
	drawtxt(window, "Start", resolutionx / 2, resolutiony / 2, 60);
}

void update_settings() {
	if (mouse_pressed == true)
	{
		Rectangle rec;
		rec.x = 366;
		rec.y = 253;
		rec.max_x = 100;
		rec.max_y = 40;
		if (in_Rectangle(rec, mousex, mousey))
			std::exit(0);
		else
			next_menu(menu_Type::basic_menu);
	}
}

void render_settings(sf::RenderWindow& window) {
	drawtxt(window, "Resolution", 363, 232, 60);
	drawtxt(window, "Vertical Sinhronization", 220, 232, 60);
}

void update_game_scene() {
	// добавить объекты из очереди для спавна:
	for (const auto& spawn_fn : spawn_order)
		spawn_fn();
	spawn_order.clear();

	game_master();
	update_dps_numbers();

	// спавним врагов, пока не в магазине
	if (game_time % 100 == 0)
		if (wawe == true && shop == false)
		  makebot1();

	// физика объектов
	for (auto& object : objects)
		game_object_control(object);

	// проверка столкновений
	if (objects.size() > 1)
		for (int a = 0; a < objects.size() - 1; ++a)
			for (int b = a; b < objects.size(); ++b)
				if (&objects[a] != &objects[b])
					if (collision_filter(objects[a], objects[b]))
						if (circles_collide(objects[a], objects[b]) == true)
							damage(objects[a], objects[b]);

	// если волна кончилась, можно идти в магаз
	if (!objects.empty()) {
		auto& player = objects[0];
		if (player.x >= resolutionx - 10 && wawe == false)
			next_menu(menu_Type::shop);
	}

	// смерть объектов
	std::erase_if(objects, [](Game_Object& obj) { 
		bool hp_zero = obj.hp <= 0;
		// запуск функций при смерти объекта
		if (obj.dead_function && hp_zero == true) {
			obj.dead_function(obj);
			hp_zero = obj.hp <= 0;
		}
		return hp_zero;
	});
}

inline auto update_menu_func = &update_mainmenu;
inline auto render_menu_func = &render_mainmenu;

void render_game_scene(sf::RenderWindow& window) {
	std::string txt = "difficulty " + std::to_string(difficulty);
	std::string healt = "hp " + std::to_string(objects[0].hp);
	std::string enemy_count = "enemy count " + std::to_string(enemy_info());
	std::string coin_count = "coincount " + std::to_string((int)money);
	drawtxt(window, coin_count, 5, 90, 30);
	drawtxt(window, enemy_count, 5, 50, 30);
	drawtxt(window, txt, 5, 25, 20);
	drawtxt(window, healt, resolutionx - 100, 5, 20);
	drawtxt(window, std::to_string(game_time / 200), resolutionx - 100, 25, 20);
	for (auto& object : objects)
	{
		if ( !draw_texture(window, object.texture, object.x, object.y)) {
			rendercircle(window, object.x, object.y, object.hitbox, object.color);
		}
	}
	draw_dps_numbers(window);
}

// случайные предметы в магазе
shop_item random_shop_item() {
	auto sz = items_base.size();
	auto idx = rand() % sz;
	int i = 0;
	for (const auto& [key, val] : items_base) {
		if (i == idx)
			return val;
		++i;
	}
	return items_base.begin()->second;
}

void update_shop() {
	if (wawe == false && enemy_info() == 0) {
		wawe = true;
		auto& player = objects[0];
		player.x = resolutionx / 2;
		player.y = resolutiony / 2;
		int id_items = 0;
		//добавление предмета
		for (int i = 0; i < 3; ++i)
			shop_items.push_back(random_shop_item());

		for (auto item : shop_items) {
			Game_Object button;
			button.type = Type::button;
			button.hitbox = 40;
			button.color = { 0,0,255 };
			button.hp = button.max_hp = 10;
			button.damage = 0;
			button.x = 110;
			button.y = 140 + id_items * 100;
			id_items += 1;
			button.speed = 0;
			button.dead_function = [item](Game_Object& o) {
				if (money < item.coast) {
					o.hp = 10;
				} else { // тут покупка
					auto& player = objects[0];
					money -= item.coast;
					player.gold_passive += item.passive_gold;
					player.x2_gold += item.x2_coins_chance;
					player.slowdown += item.movment_slowdown;
					player.vampirism += item.vampirism;
					player.damage += player.damage * item.Damage_Reflection;
				}
			};
			spawn(button);
		}
		shop = true;
	}
	update_game_scene();
}

void render_shop(sf::RenderWindow& window) {
	render_game_scene(window);
	if (shop == false)
		return;
	drawtxt(window, "shop", 600, 5, 50);
	int id_items = 0;
	for (auto item : shop_items) {
		drawtxt(window, item.name, 25, 100+id_items*100, 50);
		drawtxt(window, std::to_string(item.coast), 25, 150 + id_items * 100, 30);
		id_items ++;
	}
}

void update_menu() {
	// проверить что ESC нажали, а потом отпустили
	static bool prev_key = false;
	bool key_esc = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape);
	if (key_esc == true) {
		prev_key = true;
	} else if (prev_key == true) {
		prev_key = false;
		back();
	}

	// проверка что меню закончились
	if (history_of_menu.empty())
		return;
	
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
