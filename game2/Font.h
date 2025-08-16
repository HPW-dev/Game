#pragma once
#include <string>
#include "potato-sfml.h"

void loadingfont(std::string fontname);
void drawtxt(sf::RenderWindow& window, std::string text, float x, float y, int size,
	sf::Color color = sf::Color(255, 255, 255));
