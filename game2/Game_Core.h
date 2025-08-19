#pragma once
#include <iostream>
#include "potato-sfml.h"
#include "Misc.h"

constexpr int DEFAULT_RES_X = 1280;
constexpr int DEFAULT_RES_Y = 720;
inline int resolutionx = DEFAULT_RES_X;
inline int resolutiony = DEFAULT_RES_Y;
inline float mousex;
inline float mousey;
inline bool mouse_pressed = false;
inline int game_time = 0;
inline float difficulty = 1;
inline const float difficulty_max_default = 1.5f;
inline float difficulty_max = difficulty_max_default; // сколько сложности набрать для смены уровня
inline float difficulty_for_boss_max = 2.f;
inline bool wawe = true;
inline bool shop = false;
inline float money = 0;
inline bool fullscreen = false;
inline bool kill_boss = false;
inline bool boss_defeated = false;
inline bool boss_spawned = false;
inline sf::Color bg_color = sf::Color(0,0,0); // цвет фона

inline void game_master() {
	if (difficulty >= difficulty_max) {
		wawe = false;
		difficulty_max *= 1.2f;
		std::cout << "for next level: " << difficulty_max << "\n";
	}
	// рост сложности
	if (wawe == true && shop == false)
		difficulty += 0.00004f;

	if (!boss_spawned && difficulty >= difficulty_for_boss_max) {
		kill_boss = true;
		boss_defeated = false;
		difficulty_for_boss_max += 2.f;
	}

	if (boss_spawned) {
		shop = false;
		wawe = false;
		bg_color = sf::Color(0, 32, 0);
	} else {
		bg_color = sf::Color(0, 0, 0);
	}

	if (shop)
		bg_color = sf::Color(0, 16, 32);
}

