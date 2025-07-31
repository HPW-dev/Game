#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
inline sf::Font mainfont;
void loadingfont(std::string fontname ) {
	auto result= mainfont.openFromFile(fontname);
	if (result == false) {
		std::cout << "no font\n";
	}
}
void drawtxt(sf::RenderWindow& window, std::string text, float x, float y, int size) {
	sf::Text txt(mainfont);
	txt.setString(text);
	txt.setCharacterSize(size);
	txt.setPosition({ x,y });
	txt.setFillColor({ 255, 255, 255 });
	window.draw(txt);
}