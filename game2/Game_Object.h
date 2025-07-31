#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

enum class Type {
	none,
	player,
	bot1,
	bullet,
	coin,
	button,
};

struct Game_Object {
	double gold_passive = 0; // если > 0, то золото будет капать каждый кадр
	double x = 0, y = 0;
	double hitbox = 0;
	sf::Color color;
	double hp = 0;
	double damage = 0;
	Type type;
	double speed = 0;
	double buff_on_damage = 0;
	double buff_on_def = 0;
	double buf_on_recharge_speed = 0;
	double buff_on_speed = 0;
	double radius_of_weapon = 0;
	double weapon_size = 0;
	double vx = 0, vy = 0;
	int shot_delay = 0;
	int shot_time = 0;
	double max_hp = 0;
	double regen = 0;
	double slowdown = 0; // <-- movement slowdown
	double vampirism = 0;
	double combustion = 0;
	double x2_gold = 0;
	int life_time = 0;
	Type creator;
	std::function <void(Game_Object&)> dead_function;
};
