#include <cmath>
#include "potato-sfml.h"
#include "Misc.h"
#include "Game_Object.h"
#include "Objects.h"
#include "dps-numbers.h"

double rand_double() {
	return rand() / double(RAND_MAX);
}

void rendercircle(sf::RenderWindow& window, float x, float y, float radius, sf::Color color) {
	sf::CircleShape circle(radius);
	circle.setPosition({ x - radius,y - radius });
	circle.setFillColor(color);
	window.draw(circle);
}

float pow2(float number) {
	return number * number;
}

float distance(float x0, float y0, float x1, float y1) {
	return std::sqrt(pow2(x0 - x1) + pow2(y0 - y1));
}

bool circles_collide(const Game_Object& a, const Game_Object& b) {
	auto dx = b.x - a.x;
	auto dy = b.y - a.y;
	auto distance_squared = pow2(dx) + pow2(dy);
	auto sum_radius = a.hitbox * a.size + b.hitbox * b.size;
	return distance_squared <= sum_radius * sum_radius;
}

void damage(Game_Object& a, Game_Object& b) {
	a.hp -= std::max(0.f, b.damage - (b.damage * a.armor));
	b.hp -= std::max(0.f, a.damage - (a.damage * b.armor));
	add_dps_number(a.x - 10.f, a.y - 10.f, b.damage);
	add_dps_number(b.x + 10.f, b.y - 20.f, a.damage);

	// обработка вампиризма:
	if (
		(a.type == Type::bot1 && b.type == Type::bullet) ||
		(b.type == Type::bot1 && a.type == Type::bullet)
		) {
		auto& player = objects.at(0);
		auto damage = a.type == Type::bot1 ? a.damage : b.damage;
		player.hp += damage * player.vampirism;
	}

	// обработка замедления:
	if (b.type == Type::bullet) a.speed = std::max(0.f, a.speed - b.movement_slowdown);
	if (a.type == Type::bullet) b.speed = std::max(0.f, b.speed - a.movement_slowdown);
}

bool collision_filter(Game_Object& a, Game_Object& b) {
#define collision_ready(A, B) \
if (a.type == Type::A && b.type == Type::B) \
  return true; \
if (a.type == Type::B && b.type == Type::A) \
  return true;

	collision_ready(bullet, bot1)
		collision_ready(player, bot1)
		collision_ready(player, coin)
		collision_ready(player, button)
#undef collision_ready
		return false;
}

int enemy_info() {
	int enemys = 0;

	for (auto& enemy : objects)
		if (enemy.type == Type::bot1 && enemy.hp >= 1)
			enemys += 1;

	return enemys;
}

// список объектов на добавление
static std::vector<std::function<void()>> spawn_order;

// безопасный спавн объектов
void spawn(const Game_Object& obj) {
	spawn_order.push_back([o = obj] {
		objects.push_back(o);
		});
}

void spawn_processing() {
	for (const auto& spawn_fn : spawn_order)
		spawn_fn();
	spawn_order.clear();
}
