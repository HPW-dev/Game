#pragma once
#include <iostream>
#include "Misc.h"

inline int resolutionx = 1280;
inline int resolutiony = 720;
inline int mousex;
inline int mousey;
inline bool mouse_pressed = false;
inline int game_time = 0;
inline double difficulty = 1;
inline double difficulty_max = 1.5; // сколько сложности набрать для смены уровня
inline bool wawe = true;
inline bool shop = false;
inline double money = 0;

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
