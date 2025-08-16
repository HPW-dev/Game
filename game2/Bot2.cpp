#pragma once
#include <cmath>
#include "Bot2.h"
#include "Game_Object.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Misc.h"
#include "Player.h"
#include "dps-numbers.h"

// превращение в монетку
/*static void dead(Game_Object& coin) {
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
}*/

void make_bot_2() {
	int angle = rand() % 360;
	auto x = std::cos(angle);
	auto y = std::sin(angle);
	// заспавнить бота за экраном
	const auto spawn_dist = resolutionx / 2.0 + 100;
	x *= spawn_dist;
	y *= spawn_dist;
	x += resolutionx / 2.0;
	y += resolutiony / 2.0;
    
	Game_Object bot2;
	bot2.type = Type::bot_archer;
	bot2.x = static_cast<float>(x);
	bot2.y = static_cast<float>(y);
	bot2.difficulty_plus = 0.02f;
	bot2.speed = 0.3f * difficulty;
	bot2.hitbox = 15;
	bot2.color = { 255,0,0 };
	bot2.hp = bot2.max_hp = 20 * difficulty;
	bot2.damage = 0.2f * difficulty;
    bot2.is_enemy = true;
	bot2.shot_delay = 2 * 200;
	bot2.shot_time = rand() % bot2.shot_delay;
	//bot2.texture = "bot_1";
	//bot2.dead_function = &dead;
	spawn(bot2);
}

void shot_to_player(Game_Object& bot, const Game_Object& target) {
	Game_Object bullet;
	bullet.type = Type::bot_bullet;
	
	float x = target.x - bot.x;
	float y = target.y - bot.y;
	float diff = distance(target.x, target.y, bot.x, bot.y);
	x /= diff;
    y /= diff;
	float BULLET_SPEED = 1.f;
    x *= BULLET_SPEED;
    y *= BULLET_SPEED;
	bullet.vx = x;
	bullet.vy = y;
	bullet.x = bot.x;
	bullet.y = bot.y;

	bullet.speed = BULLET_SPEED;
	bullet.hitbox = 10;
	bullet.color = { 255,0,0 };
	bullet.hp = bullet.max_hp = 4;
	bullet.damage = 0.2f * difficulty;
    bullet.is_enemy = true;
	bullet.is_bullet = true;
	spawn(bullet);
}

void move_bot_2(Game_Object& object) {
	auto& player = get_player();
	if (player.type != Type::player)
		return;

	object.speed = std::min(object.speed, 10.f);

    // идти в направлении игрока
	double x = player.x - object.x;
	double y = player.y - object.y;
	float diff = distance(player.x, player.y, object.x, object.y);
	x /= diff;
    y /= diff;
    x *= object.speed;
    y *= object.speed;

	object.shot_time--;

	if (object.shot_time <= 0) {
		shot_to_player(object, player);
		object.shot_time = object.shot_delay;
	}

    if (diff > 300.f) { // подойти
        object.x += static_cast<float>(x);
        object.y += static_cast<float>(y);
    } else { // убежать
        object.x -= static_cast<float>(x);
        object.y -= static_cast<float>(y);
    }
}
