#pragma once
#include <cmath>
#include "Game_Object.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Misc.h"
#include "dps-numbers.h"

// превращение в монетку
void dead(Game_Object& coin) {
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
	
	// действие при поднятии монеты
	coin.dead_function = [](Game_Object& o) {
		if (o.life_time > 0) { 
			auto gold = 1000.0 / difficulty;
			const auto& player = objects.at(0);
			// шанс выпадения x2
			if (rand_double() < player.x2_gold)
				gold *= 2;
			money += gold;
			add_label(o.x+50, o.y, "+" + std::to_string(int(gold)) + "$");
		}
	};
	coin.texture = "coin";
	coin.life_time = 200 * 6;
}

void makebot1() {
	int angle = rand() % 360;
	float x = std::cos(angle);
	float y = std::sin(angle);
	x *= 1600;
	y *= 1600;
	x += objects[0].x;
	y += objects[0].y;
	Game_Object bot1;
	bot1.type = Type::bot1;
	bot1.x = x;
	bot1.y = y;
	bot1.difficulty_plus = 0.02;
	bot1.speed = 0.2*difficulty;
	bot1.hitbox = 15;
	bot1.color = { 0,255,0 };
	bot1.hp = bot1.max_hp = 30*difficulty;
	bot1.damage = 0.2*difficulty;
	bot1.texture = "bot_1";
	bot1.dead_function = &dead;
	spawn(bot1);
}
void move_bot(Game_Object& object) {
	auto& player = objects[0];
	if (player.type != Type::player)
		return;

	double x = player.x - object.x;
	double y = player.y - object.y;
	float diff = distance(player.x,player.y,object.x,object.y);
	x /= diff;
	y /= diff;
	x *= object.speed;
	y *= object.speed;
	object.x += x;
	object.y += y;
}
