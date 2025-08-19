#include <ctime>
#include "potato-sfml.h"
#include "Player.h"
#include "Bot1.h"
#include "Menu.h"
#include "Font.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Misc.h"
#include "Game_Object.h"
#include "Graphic.h"

void loading_textures() {
  load_texture("player", "Resources/Images/Main_hero.png");
  load_texture("bullet", "Resources/Images/def_bullet.png");
  load_texture("bot_1", "Resources/Images/bot_1.png");
  load_texture("coin", "Resources/Images/coin.png");
}

void set_fullscreen(sf::RenderWindow& window, bool mode) {
  if (mode) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    resolutionx = desktopMode.size.x;
    resolutiony = desktopMode.size.y;
    //window.setPosition({0,0} );
    //window.setSize(sf::Vector2u(resolutionx, resolutiony));
    window.create(desktopMode, "Fullscreen PotatoII", sf::State::Fullscreen);
    //window.create(mode, "PotatoII", sf::Style::None, sf::State::Windowed);
  } else {
    resolutionx = DEFAULT_RES_X;
    resolutiony = DEFAULT_RES_Y;
    auto mode = sf::VideoMode(sf::Vector2u(resolutionx, resolutiony));
    window.create(mode, "PotatoII");
  }

  window.setFramerateLimit(200);
  window.setVerticalSyncEnabled(false);
}

int main() {
    const auto launch_time = static_cast<unsigned>(time({}));
    srand(launch_time); // для разной случайной генерации

    next_menu(menu_Type::basic_menu);
    int fps = 0;
    std::string fps_txt;
    sf::Vector2u size(resolutionx, resolutiony);
    auto mode = sf::VideoMode(size);
    sf::RenderWindow window(mode, "PotatoII");
    window.setFramerateLimit(200);
    window.setVerticalSyncEnabled(false);
    auto time_st = std::clock();
    loadingfont("Word Gothic.ttf");
    loading_textures();

    while (window.isOpen()) {//главный цикл игры
        game_time += 1;
        while (auto event = window.pollEvent()) {
            bool is_closed = event->is<sf::Event::Closed>();
            //bool is_escape = event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape;
            if (is_closed) window.close();
            //if (is_escape) back();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LAlt)) {
          fullscreen = !fullscreen;
          set_fullscreen(window, fullscreen);
        }
    
        /* условия для выхода: Выйти через кнопку
        Escape или через нажатие по крестику на окне */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
          sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
          mousex = static_cast<float>(globalPosition.x);
          mousey = static_cast<float>(globalPosition.y);
          mouse_pressed = true;
        }
        else {
          mouse_pressed = false;
        }

        update_menu();

        auto time_now = std::clock();
        auto eps = (time_now - time_st) / double(CLOCKS_PER_SEC);
        if (eps >= 1.0) {
          fps_txt = "FPS: " + std::to_string(int(fps / eps));
          time_st = time_now;
          fps = 0;
        }

        window.clear(); // стереть предыдущий кадр
        menu_render(window);
        drawtxt(window, fps_txt, 5, 5, 20);
        fps += 1;
        window.display(); // показать кадр
    }
}