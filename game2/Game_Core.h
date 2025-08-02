#pragma once
#include <iostream>
#include "Misc.h"

constexpr int DEFAULT_RES_X = 1280;
constexpr int DEFAULT_RES_Y = 720;
inline int resolutionx = DEFAULT_RES_X;
inline int resolutiony = DEFAULT_RES_Y;
inline int mousex;
inline int mousey;
inline bool mouse_pressed = false;
inline int game_time = 0;
inline double difficulty = 1;
inline double difficulty_max = 1.5; // сколько сложности набрать для смены уровня
inline bool wawe = true;
inline bool shop = false;
inline double money = 0;
inline bool fullscreen = false;

void game_master() {
	if (difficulty >= difficulty_max) {
		wawe = false;
		difficulty_max *= 1.5;
		std::cout << "for next level: " << difficulty_max << "\n";
	}
	// рост сложности
	if (wawe == true && shop == false)
		difficulty += 0.0001;
}

