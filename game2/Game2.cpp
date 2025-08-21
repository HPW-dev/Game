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
#include "Sound.h"

void loading_textures() {
  load_texture("player", "Resources/Images/Main_hero.png");
  load_texture("bullet", "Resources/Images/def_bullet.png");
  load_texture("slime", "Resources/Images/slime.png");
  load_texture("coin", "Resources/Images/coin.png");
  load_texture("bg_for_menu", "Resources/Images/bg_for_menu.png");
  load_texture("bg_shop", "Resources/Images/bg_shop.jpg");
  load_texture("bg_for_game", "Resources/Images/bg_for_game.png");
  load_texture("chest", "Resources/Images/chest.png");
}

void loading_sounds() {
  load_sound("music_1", "Resources/Audio/01 - Falling Apart (Prologue).mp3", true);
  load_sound("music_2", "Resources/Audio/02 - Title Theme.mp3", true);
  load_sound("music_3", "Resources/Audio/03 - Definitely Our Town.mp3", true);
  load_sound("music_4", "Resources/Audio/04 - Silent Forest.mp3", true);
  load_sound("music_5", "Resources/Audio/05 - Battle 1.mp3", true);
  load_sound("music_6", "Resources/Audio/06 - Victory!.mp3", true);
  load_sound("music_7", "Resources/Audio/07 - Port Town.mp3", true);
  load_sound("music_8", "Resources/Audio/08 - Shop.mp3", true);
  load_sound("music_9", "Resources/Audio/09 - Battle 2.mp3", true);
  load_sound("music_10", "Resources/Audio/10 - Lost Shrine.mp3", true);
  load_sound("music_11", "Resources/Audio/11 - The Mighty Kingdom.mp3", true);
  load_sound("music_12", "Resources/Audio/12 - Frozen Abyss.mp3", true);
  load_sound("music_13", "Resources/Audio/13 - Decisive Battle 1 - Don't Be Afraid.mp3", true);
  load_sound("music_14", "Resources/Audio/14 - Tales of Firelight Town.mp3", true);
  load_sound("music_15", "Resources/Audio/15 - Peaceful Night.mp3", true);
  load_sound("music_16", "Resources/Audio/16 - The Calm Before The Storm.mp3", true);
  load_sound("music_17", "Resources/Audio/18 - Never Give Up.mp3", true);
  load_sound("music_18", "Resources/Audio/19 - Where The Winds Roam.mp3", true);
  load_sound("music_19", "Resources/Audio/20 - The Journey.mp3", true);
  load_sound("music_20", "Resources/Audio/21 - Final Battle - For Love.mp3", true);
  load_sound("music_21", "Resources/Audio/22 - The Final of The Fantasy.mp3", true);
  load_sound("bullet_sound", "Resources/Audio/bullet_sound.ogg");

  int rnd = (rand() % 21) + 1; // рандомный номер трека
  play_sound("music_" + std::to_string(rnd), 1.f);
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
    loading_sounds();

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