#include "menu-shop.h"
#include "Items.h"
#include "Game_Core.h"
#include "Objects.h"
#include "menu-game.h"
#include "Font.h"
#include "Player.h"

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
		auto& player = get_player();
		player.x = resolutionx / 2.f;
		player.y = resolutiony / 2.f;
		int id_items = 0;
		//добавление предмета
		for (int i = 0; i < 3 + (rand() % 3); ++i)
			shop_items.push_back(random_shop_item());

		for (auto& item : shop_items) {
			Game_Object button;
			button.type = Type::button;
			button.hitbox = 40;
			button.color = { 0,0,255 };
			button.hp = button.max_hp = 10;
			button.damage = 0;
			button.x = 110;
			button.y = 140.f + id_items * 100.f;
			id_items += 1;
			button.speed = 0;
			button.dead_function = [&](Game_Object& o) {
				if (money < item.coast) {
					o.hp = 10;
				} else { // тут покупка
					auto& player = get_player();
					money -= item.coast;
					if (item.action)
						item.action(player);
					item.buy = true;
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
		if (!item.buy) {
			drawtxt(window, item.name, 25, 100.f + id_items * 100.f, 50);
			drawtxt(window, std::to_string(item.coast), 25, 150.f + id_items * 100.f, 30);
		}
		id_items++;
	}
}
