#include <ctime>

#pragma warning(push)
#pragma warning(disable: 4275)
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#pragma warning(pop)

#include "Player.h"
#include "Bot1.h"
#include "Menu.h"
#include "Font.h"
#include "Game_Core.h"
#include "Misc.h"
#include "Game_Object.h"

int main() {
    srand( time(0) ); // для разной случайной генерации

    next_menu(menu_Type::basic_menu);
    int fps = 0;
    std::string fps_txt;
    sf::Vector2u size(resolutionx, resolutiony);
    sf::RenderWindow window(sf::VideoMode(size), "SFML Window");
    window.setFramerateLimit(200);
    window.setVerticalSyncEnabled(false);
    auto time_st = std::clock();
    loadingfont("Word Gothic.ttf");

    while (window.isOpen()) {//главный цикл игры
        game_time += 1;
        while (auto event = window.pollEvent()) {
            bool is_closed = event->is<sf::Event::Closed>();
            bool is_escape = event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape;
            if (is_closed) window.close();
            if (is_escape) back();
        }
    
        /* условия для выхода: Выйти через кнопку
        Escape или через нажатие по крестику на окне */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
          sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
          mousex = globalPosition.x;
          mousey = globalPosition.y;
          mouse_pressed = true;
        }
        else {
          mouse_pressed = false;
        }

        update_menu();

        if (history_of_menu.empty())
            next_menu(menu_Type::yes_no);

        auto time_now = std::clock();
        auto eps = (time_now - time_st) / double(CLOCKS_PER_SEC);
        if (eps >= 1.0) {
          fps_txt = "FPS: " + std::to_string(int(fps / eps));
          time_st = time_now;
          fps = 0;
        }

        window.clear(); // стереть предыдущий кадр
        render_menu_func(window);
        drawtxt(window, fps_txt, 5, 5, 20);
        fps += 1;
        window.display(); // показать кадр
    }
}