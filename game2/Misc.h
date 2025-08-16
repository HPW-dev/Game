#pragma once
#include "potato-sfml.h"
#include "Game_Object.h"

double rand_double();
void rendercircle(sf::RenderWindow& window, float x, float y, float radius, sf::Color color);
float pow2(float number);
float distance(float x0, float y0, float x1, float y1);
bool circles_collide(const Game_Object& a, const Game_Object& b);
void damage(Game_Object& a, Game_Object& b);
bool collision_filter(Game_Object& a, Game_Object& b);
int enemy_info();
void spawn(const Game_Object& obj); // безопасный спавн объектов
void spawn_processing();
