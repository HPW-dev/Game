#include "Font.h"
#include <iostream>

static sf::Font mainfont;

void loadingfont(std::string fontname) {
	auto result = mainfont.openFromFile(fontname);
	if (result == false) {
		std::cout << "no font\n";
	}
}

void drawtxt(sf::RenderWindow& window, std::string text, float x, float y, int size, sf::Color color) {
	sf::Text txt(mainfont);
	txt.setString(text);
	txt.setCharacterSize(size);
	txt.setPosition({ x,y });
	txt.setFillColor(color);
	txt.setOutlineColor(sf::Color(0, 0, 0)); // чёрный контур текста
	txt.setOutlineThickness(3);
	window.draw(txt);
}

