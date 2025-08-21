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
static void make_money(Game_Object& boss) {
	for (int i = 0; i < 20 + rand() % 50; ++i) {
		Game_Object coin;
		coin.x = boss.x + (rand_double() * 2.f - 1.f) * 100.f;
		coin.y = boss.y + (rand_double() * 2.f - 1.f) * 100.f;
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
				auto gold = 1500.f / (difficulty * 0.9f);
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
		spawn(coin);
	}

    kill_boss = false;
	boss_defeated = true;
    boss_spawned = false;

	// за убийство бота повышение сложности
	//if (wawe == true)
	//	difficulty += coin.difficulty_plus;
}

void make_boss() {
	int angle = rand() % 360;
	auto x = std::cos(angle);
	auto y = std::sin(angle);
	// заспавнить бота за экраном
	const auto spawn_dist = resolutionx / 2.0 + 100;
	x *= spawn_dist;
	y *= spawn_dist;
	x += resolutionx / 2.0;
	y += resolutiony / 2.0;
    
	Game_Object e;
	e.type = Type::boss1;
	e.x = static_cast<float>(x);
	e.y = static_cast<float>(y);
	e.difficulty_plus = 0.02f;
	e.speed = 0.1f * difficulty;
	e.hitbox = 50;
	e.color = { 255,128,0 };
	e.hp = e.max_hp = 10'000 * difficulty;
	e.damage = 0.4f * difficulty;
    e.is_enemy = true;
	e.shot_delay = 2 * 300;
	e.shot_time = rand() % e.shot_delay;
	//e.texture = "bot_1";
	e.dead_function = &make_money;
	spawn(e);
}

static void shot_to_player(Game_Object& bot, const Game_Object& target) {
    for (int i = 0; i < 10 + rand() % 30; ++i) {
        Game_Object bullet;
        bullet.type = Type::bot_bullet;
        
        float x = target.x - bot.x + (rand_double() * 2.0 - 1.0) * 150.0;
        float y = target.y - bot.y + (rand_double() * 2.0 - 1.0) * 150.0;
        float diff = distance(target.x, target.y, bot.x, bot.y);
        x /= diff;
        y /= diff;
        float BULLET_SPEED = 4.0f;
        x *= BULLET_SPEED;
        y *= BULLET_SPEED;
        bullet.vx = x;
        bullet.vy = y;
        bullet.x = bot.x + (rand_double() * 2.0 - 1.0) * 30.0;
        bullet.y = bot.y + (rand_double() * 2.0 - 1.0) * 30.0;

        bullet.speed = BULLET_SPEED;
        bullet.hitbox = 6;
        bullet.color = { 255,0,0 };
        bullet.hp = bullet.max_hp = 4;
        bullet.damage = 1.f * difficulty;
        bullet.is_enemy = true;
        bullet.is_bullet = true;
        spawn(bullet);
    }
}

void move_boss(Game_Object& object) {
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

    if (diff > 200.f) { // подойти
        object.x += static_cast<float>(x);
        object.y += static_cast<float>(y);
    } else { // убежать
        object.x -= static_cast<float>(x);
        object.y -= static_cast<float>(y);
    }
}
