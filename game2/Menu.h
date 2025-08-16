#pragma once
#include "potato-sfml.h"

enum class menu_Type {
	basic_menu,
	game_scene,
	settings,
	yes_no,
	results,
	shop,
};

void next_menu(menu_Type menu); // ����� ���������� ����
void back(); // ����� � ���������� ����
void update_menu();
void menu_render(sf::RenderWindow& window);
