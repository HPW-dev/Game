#pragma once
#include <string>
#include <SFML/Graphics.hpp>

// ��������� �������� - file ��� �������� �����
void load_texture(std::string name, std::string file);
// ���������� �������� �� ������
bool draw_texture(sf::RenderWindow& window, std::string name, float x, float y, float scale=1.0);
