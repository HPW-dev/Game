#pragma once
#include <string>
#include <SFML/Graphics.hpp>

// загрузить текстуру - file это название файла
void load_texture(std::string name, std::string file);
// нарисовать текстуру на экране
bool draw_texture(sf::RenderWindow& window, std::string name, float x, float y, float scale=1.0);
