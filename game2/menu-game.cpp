#include "menu-game.h"
#include "Game_Core.h"
#include "Bot1.h"
#include "Bot2.h"
#include "Boss.h"
#include "Graphic.h"
#include "Game_object_control.h"
#include "Menu.h"
#include "Misc.h"
#include "Objects.h"
#include "dps-numbers.h"

void update_game_scene() {
	// добавить объекты из очереди для спавна:
	spawn_processing();

	game_master();
	update_dps_numbers();

	// спавним врагов, пока не в магазине
	if (game_time % 150 == 0)
		if (wawe == true && shop == false) {
			// спавнить ещё больше врагов
			const int count = std::ceil(1 + (difficulty / 4) * 2);
			for (int i = 0; i < count; ++i)
				makebot1();

			// второй вид противника
			if (difficulty >= 6.0f)
				for (int i = 0; i < count; ++i)
					make_bot_2();
		}

	if (kill_boss && !boss_spawned) {
		boss_spawned = true;
		make_boss();
	}

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
		auto& player = get_player();
		if (player.x >= resolutionx - 10 && wawe == false)
			next_menu(menu_Type::shop);
	}

	// смерть объектов
	std::erase_if(objects, [](Game_Object& obj) {
		bool hp_zero = obj.hp <= 0;
		// применение воскрешения
		if (obj.resurections > 0) {
			obj.resurections -= 1;
			obj.hp = obj.max_hp;
			std::cout << "Resurected!\n";
			return false;
		}
		// запуск функций при смерти объекта
		if (obj.dead_function && hp_zero == true) {
			obj.dead_function(obj);
			hp_zero = obj.hp <= 0;
		}
		return hp_zero;
	});
}

void render_game_scene(sf::RenderWindow& window) {
	window.clear();
	draw_texture(window, background, resolutionx/2,resolutiony/2, fullscreen ? 2.f : 1.f);
	std::string txt = "difficulty " + std::to_string(difficulty);
	std::string healt = "hp " + std::to_string(int(get_player().hp));
	std::string enemy_count = "enemy count " + std::to_string(enemy_info());
	std::string coin_count = "coincount " + std::to_string((int)money);
	drawtxt(window, coin_count, 5, 90, 30);
	drawtxt(window, enemy_count, 5, 50, 30);
	drawtxt(window, txt, 5, 25, 20);
	drawtxt(window, healt, resolutionx - 100.f, 5, 20);
	drawtxt(window, std::to_string(game_time / 200), resolutionx - 100.f, 25, 20);
	for (auto& object : objects) {
		if (!draw_texture(window, object.texture, object.x, object.y, object.size)) {
			rendercircle(window, object.x, object.y, object.hitbox * object.size, object.color);
		}
	}
	draw_dps_numbers(window);
}
