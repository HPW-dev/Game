#pragma once
#include <vector>
#include "Font.h"
#include "potato-sfml.h"

struct Dps_number {
    std::string number {};
    sf::Vector2f pos {};
    int lifetime = 250;
    sf::Color color{};
};

// добавить надпись об уроне
void add_dps_number(float x, float y, float damage);
// любая надпись над объектом
void add_label(float x, float y, std::string text, sf::Color color=sf::Color(255, 255, 0));
void draw_dps_numbers(sf::RenderWindow& wnd);
void update_dps_numbers();
