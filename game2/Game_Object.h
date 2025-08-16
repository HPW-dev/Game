#pragma once
#include <functional>
#include "potato-sfml.h"

enum class Type {
	none,
	player,
	bot1,
	bullet,
	coin,
	button,
};

struct Game_Object {
	float gold_passive = 0; // если > 0, то золото будет капать каждый кадр
	float damage = 0;
	float speed = 0;
	float size = 1;
	float max_hp = 0;
	float regen = 0;
	float movement_slowdown = 0;
	float vampirism = 0;
	float coast_plus = 0;
	float combustion = 0;
	float x2_gold = 0;
	float HP_to_damage_ratio = 0;
	int shot_delay = 0;
	int resurections = 0;
	sf::Color color;
	std::string texture {}; // картинка объекта
	std::function <void(Game_Object&)> dead_function{};
	float x = 0, y = 0;
	float hitbox = 0;
	float hp = 0;
	float vx = 0, vy = 0;
	float difficulty_plus = 0;
	int life_time = 0;
	int shot_time = 0;
	float shot_time_max = 15.f;
	float armor = 0;
	unsigned bullets = 1;
	float coin_to_hp = 0;
	Type type{};
	Type creator{}; // тот, кто создал объект
};
