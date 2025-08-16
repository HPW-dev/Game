#pragma once
#include <iostream>
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
inline bool wawe = true;
inline bool shop = false;
inline float money = 0;
inline bool fullscreen = false;

inline void game_master() {
	if (difficulty >= difficulty_max) {
		wawe = false;
		difficulty_max *= 1.2f;
		std::cout << "for next level: " << difficulty_max << "\n";
	}
	// рост сложности
	if (wawe == true && shop == false)
		difficulty += 0.00004f;
}

