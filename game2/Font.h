#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
inline sf::Font mainfont;

inline void loadingfont(std::string fontname ) {
	auto result= mainfont.openFromFile(fontname);
	if (result == false) {
		std::cout << "no font\n";
	}
}
inline void drawtxt(sf::RenderWindow& window, std::string text, float x, float y, int size,
sf::Color color=sf::Color(255,255,255)) {
	sf::Text txt(mainfont);
	txt.setString(text);
	txt.setCharacterSize(size);
	txt.setPosition({ x,y });
	txt.setFillColor(color);
	window.draw(txt);
}