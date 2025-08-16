#pragma once
#include <string>
#include "potato-sfml.h"

// загрузить текстуру - file это название файла
void load_texture(std::string name, std::string file);
// нарисовать текстуру на экране
bool draw_texture(sf::RenderWindow& window, std::string name, float x, float y, float scale=1.0);
