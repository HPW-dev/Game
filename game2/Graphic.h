#pragma once
#include <string>
#include "potato-sfml.h"

// ��������� �������� - file ��� �������� �����
void load_texture(std::string name, std::string file);
// ���������� �������� �� ������
bool draw_texture(sf::RenderWindow& window, std::string name, float x, float y, float scale=1.0);
