#pragma once
#include "Rec.h"
#include "potato-sfml.h"
#include <string>
#include <functional>

// Тип данных для действий при нажатии на кнопку
using Action = std::function<void ()>;

struct Button {
    std::string text {}; // текст на кнопке
    float text_offset_x {}; // смещение текста на кнопке
    float text_offset_y {};
    float text_size = 36; // размер шрифта
    Rectangle rectangle {}; // размер поля нажатия на кнопку
    std::string click_sound {}; // звук при нажатии
    std::string texture {}; // название картинки на кнопку
    float texture_size {1};
    Action action {}; // действие при нажатии
};
/*
Пример создания кнопки старт
Button start;
start.title ="Start";
start.text_size = 32;
start.image = "start texture";
start.rectangle = Rec(500, 400, 200, 20);
start.action = []{ std::cout << "работает\n"; };
*/

// проверка что на кнопку нажали и запуск действий
bool check(Button& btn);
void draw(sf::RenderWindow& wnd, const Button& btn);
