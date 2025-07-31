#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Font.h"

struct Dps_number {
    std::string number {};
    sf::Vector2f pos {};
    int lifetime = 250;
};

// список надписей с уроном на экране
inline std::vector<Dps_number> dps_numbers {};

// добавить надпись об уроне
inline void add_dps_number(float x, float y, float damage) {
    if (damage < 1)
        return;
    Dps_number title;
    title.pos.x = x;
    title.pos.y = y;
    title.number = std::to_string(int(damage));
    dps_numbers.push_back(title);
}

inline void draw_dps_numbers(sf::RenderWindow& wnd) {
    for (const auto& title : dps_numbers) {
        drawtxt(wnd, title.number, title.pos.x, title.pos.y, 20);
    }
}

inline void update_dps_numbers() {
    for (auto& title : dps_numbers) {
        title.lifetime--;
        title.pos.y -= 0.2; // двигать надпись вверх
        title.pos.x += (rand() % 3 - 1) * 0.3;
    }
    // убить все надписи, у которых кончилось время
    std::erase_if(dps_numbers, [](Dps_number& title) { 
		return title.lifetime <= 0;
	});
}
