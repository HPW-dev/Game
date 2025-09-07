#pragma once
#include <iostream>
#include "potato-sfml.h"

void game_reset(const std::string& char_name={});
void update_character();
void render_character(sf::RenderWindow& window);

