#include <functional>
#include <unordered_map>
#include "Player.h"
#include "Objects.h"
#include "potato-sfml.h"
#include "Game_Core.h"
#include <iostream>
#include "Misc.h"
#include "Sound.h"
#include "Lan.h"

void makeplayer(bool lan_player, const std::string& char_name) {
  using char_maker = std::function<Game_Object ()>;
  // таблица персов
  std::unordered_map<std::string, char_maker> char_table {
    {"Mage", []()->Game_Object {
      Game_Object player;
      player.type = Type::player;
      player.x = resolutionx / 2.f;
      player.y = resolutiony / 2.f;
      player.speed = 2.5f;
      player.hitbox = 30;
      player.color = { 255,100,97 };
      player.damage = 1;
      player.max_hp = player.hp = 100;
      player.texture = "player";
      player.shot_time_max = 15;
      return player;
    }},

    {"A", []()->Game_Object {
      Game_Object player;
      player.type = Type::player;
      player.x = resolutionx / 2.f;
      player.y = resolutiony / 2.f;
      player.speed = 10.f;
      player.hitbox = 30;
      player.color = { 255,100,97 };
      player.damage = 1;
      player.max_hp = player.hp = 50;
      player.texture = "player";
      player.shot_time_max = 10;
      return player;
    }},

    {"B", []()->Game_Object {
      Game_Object player;
      player.type = Type::player;
      player.x = resolutionx / 2.f;
      player.y = resolutiony / 2.f;
      player.speed = 1.f;
      player.hitbox = 30;
      player.color = { 255,100,97 };
      player.damage = 4;
      player.max_hp = player.hp = 400;
      player.texture = "player";
      player.shot_time_max = 25;
      return player;
    }},

    {"C", []()->Game_Object {
      Game_Object player;
      player.type = Type::player;
      player.x = resolutionx / 2.f;
      player.y = resolutiony / 2.f;
      player.speed = 2.f;
      player.hitbox = 30;
      player.color = { 255,100,97 };
      player.damage = 1;
      player.max_hp = player.hp = 35;
      player.texture = "player";
      player.shot_time_max = 1;
      return player;
    }},
  }; // char_table

  Game_Object player;
  try {
    player = char_table.at(char_name)();
  }
  catch (...) {
    player = char_table.begin()->second(); // перс по умолчанию
  }

  if (lan_enabled) {
    if (lan_player)
      player.nick = "Client";
    else
      player.nick = "Server";
  }

  spawn(player);
}

// выстрел игрока
static void bullets(Game_Object& player) {
  if (player.shot_time <= 0) {
    play_sound("bullet_sound", 5.f, 2.5f + (rand() / float(RAND_MAX)) * 0.5f);

    for (unsigned i = 0; i < player.bullets; ++i) {
      Game_Object bullet;
      bullet.type = Type::bullet;
      // начальна€ позици€ пули
      float start_pos_x = ((rand() / float(RAND_MAX)) * 2.f - 1.f) * 20.f;
      float start_pos_y = ((rand() / float(RAND_MAX)) * 2.f - 1.f) * 20.f;
      bullet.x = player.x + start_pos_x * player.size;
      bullet.y = player.y + start_pos_y * player.size;
      bullet.speed = 6;
      bullet.hitbox = 10;
      bullet.color = { 173,255, 47 };
      float dist = distance(player.x, player.y, mousex, mousey);
      // разброс пули
      float angle_x = ((rand() / float(RAND_MAX)) * 2.f - 1.f) * 10.f;
      float angle_y = ((rand() / float(RAND_MAX)) * 2.f - 1.f) * 10.f;
      bullet.vx = (mousex - player.x + angle_x) / dist * bullet.speed;
      bullet.vy = (mousey - player.y + angle_y) / dist * bullet.speed;
      bullet.is_bullet = true;
      bullet.size = player.size;
      player.shot_time = std::ceil(player.shot_time_max);

      // базовый урон
      bullet.damage = player.damage * 5.f;
      // урон при лоу-хп
      auto HP_to_damage_ratio = 1.0f - (player.hp / player.max_hp);
      bullet.damage += bullet.damage * HP_to_damage_ratio * player.HP_to_damage_ratio;

      bullet.movement_slowdown += player.movement_slowdown;
      bullet.hp = bullet.max_hp = 100;
      bullet.creator = player.type;
      bullet.texture = "bullet_2";
      bullet.size = 0.2;
      
      spawn(bullet);
    }
  }
}

Game_Object& get_player() { return objects.at(0); }

void moveplayer(Game_Object& player) {
  bool key_UP = false;
  bool key_LEFT = false;
  bool key_DOWN = false;
  bool key_RIGHT = false;

  if (player.nick != "Client") {
    key_UP = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W);
    key_LEFT = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A);
    key_DOWN = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S);
    key_RIGHT = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D);
  } else {
    for (const auto& cmd: client_commands) {
      key_UP |= (cmd == "KEY|W");
      key_DOWN |= (cmd == "KEY|S");
      key_LEFT |= (cmd == "KEY|A");
      key_RIGHT |= (cmd == "KEY|D");
    }
  }
  if (key_UP) player.y -= player.speed;
  if (key_DOWN) player.y += player.speed;
  if (key_LEFT) player.x -= player.speed;
  if (key_RIGHT) player.x += player.speed;
  player.shot_time -= 1;
  //ѕроверка столкновени€ с окном
  if (player.x < 0) player.x = static_cast<float>(resolutionx);
  if (player.y < 0) player.y = static_cast<float>(resolutiony);
  if (player.x > resolutionx) player.x = 0;
  if (player.y > resolutiony) player.y = 0;

  if (player.nick == "Client") {
    // найти команду дл€ мышки
    for (const auto& cmd: client_commands) {
      auto params = split_command(cmd);
      if (params.at(0) == "MOUSE") {
        mousex = std::stod(params.at(1));
        mousey = std::stod(params.at(2));
        bullets(player);
      }
    }
  }

  // Server | ќдиночка
  if (mouse_pressed && player.nick != "Client")
      bullets(player);

  if (!shop && wawe)
    money += player.gold_passive;
}

