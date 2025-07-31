#pragma once
#include "Game_Object.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Misc.h"
#include <cmath>

// превращение в монетку
void dead(Game_Object& coin) {
	coin.dead_function = {};
	coin.type = Type::coin;
	coin.hitbox = 5;
	coin.color = { 255,255,0 };
	coin.hp = coin.max_hp = 1;
	coin.damage = 0;
	coin.speed = 0;
	coin.dead_function = [](Game_Object& o) {
		if (o.life_time > 0)
			money += 1000 / difficulty;
	};
	coin.life_time = 200 * 6;
}

void makebot1() {
	int angle = rand() % 360;
	float x = std::cos(angle);
	float y = std::sin(angle);
	x *= 1200;
	y *= 1200;
	x += objects[0].x;
	y += objects[0].y;
	Game_Object bot1;
	bot1.type = Type::bot1;
	bot1.x = x;
	bot1.y = y;
	bot1.speed = 0.2*difficulty;
	bot1.hitbox = 15;
	bot1.color = { 0,255,0 };
	bot1.hp = bot1.max_hp = 30*difficulty;
	bot1.damage = 0.2*difficulty;
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
