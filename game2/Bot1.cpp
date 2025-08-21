#pragma once
#include <cmath>
#include "Bot1.h"
#include "Game_Object.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Misc.h"
#include "Player.h"
#include "dps-numbers.h"

// превращение в монетку
static void dead(Game_Object& coin) {
	// за убийство бота повышение сложности
	if (wawe == true)
		difficulty += coin.difficulty_plus;

	coin.dead_function = {};
	coin.type = Type::coin;
	coin.hitbox = 5;
	coin.color = { 255,255,0 };
	coin.hp = coin.max_hp = 1;
	coin.damage = 0;
	coin.speed = 0;
	coin.difficulty_plus = 0;
	coin.is_enemy = false;

	// действие при поднятии монеты
	coin.dead_function = [](Game_Object& o) {
		if (o.life_time > 0) {
			auto& player = objects.at(0);
			auto gold = 1100.f / (difficulty * 0.9f);
			gold += gold * player.coast_plus;
			// шанс выпадения x2
			if (rand_double() < player.x2_gold)
				gold *= 2;
			money += gold;
			player.hp += player.coin_to_hp;
			add_label(o.x + 50, o.y, "+" + std::to_string(int(gold)) + "$");
		}
		};
	coin.texture = "coin";
	coin.life_time = 200 * 6;
}

void makebot1() {
	int angle = rand() % 360;
	auto x = std::cos(angle);
	auto y = std::sin(angle);
	// заспавнить бота за экраном
	const auto spawn_dist = resolutionx / 2.0 + 100;
	x *= spawn_dist;
	y *= spawn_dist;
	x += resolutionx / 2.0;
	y += resolutiony / 2.0;
	Game_Object bot1;
	bot1.type = Type::bot1;
	bot1.x = static_cast<float>(x);
	bot1.y = static_cast<float>(y);
	bot1.difficulty_plus = 0.02f;
	bot1.speed = 0.2f * difficulty;
	bot1.hitbox = 15;
	bot1.color = { 0,255,0 };
	bot1.hp = bot1.max_hp = 30 * difficulty;
	bot1.damage = 0.2f * difficulty;
	bot1.texture = "slime";
	bot1.dead_function = &dead;
	bot1.is_enemy = true;
	spawn(bot1);
}

void move_bot(Game_Object& object) {
	auto& player = get_player();
	if (player.type != Type::player)
		return;

	object.speed = std::min(object.speed, 10.f);

	double x = player.x - object.x;
	double y = player.y - object.y;
	float diff = distance(player.x, player.y, object.x, object.y);
	x /= diff;
	y /= diff;
	x *= object.speed;
	y *= object.speed;
	object.x += static_cast<float>(x);
	object.y += static_cast<float>(y);
}
