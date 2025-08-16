#include "Player.h"
#include "Objects.h"
#include "potato-sfml.h"
#include "Game_Core.h"
#include <iostream>
#include "Misc.h"

void makeplayer() {
  Game_Object player;
  player.type = Type::player;
  player.x = resolutionx / 2.f;
  player.y = resolutiony / 2.f;
  player.speed = 2.5f;
  player.hitbox = 30;
  player.color = { 255,100,97 };
  player.hp = 100;
  player.damage = 1;
  player.max_hp = player.hp;
  player.regen = 0;
  player.gold_passive = 0;
  player.texture = "player";
  player.shot_time_max = 15;
  spawn(player);
}

// выстрел игрока
static void bullets(Game_Object& player) {
  if (player.shot_time <= 0) {
    for (unsigned i = 0; i < player.bullets; ++i) {
      Game_Object bullet;
      bullet.type = Type::bullet;
      // начальная позиция пули
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
      bullet.texture = "bullet";
      spawn(bullet);
    }
  }
}

Game_Object& get_player() { return objects.at(0); }

void moveplayer(Game_Object& player) {
  bool key_UP = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W);
  bool key_LEFT = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A);
  bool key_DOWN = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S);
  bool key_RIGHT = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D);
  if (key_UP) player.y -= player.speed;
  if (key_DOWN) player.y += player.speed;
  if (key_LEFT) player.x -= player.speed;
  if (key_RIGHT) player.x += player.speed;
  player.shot_time -= 1;
  //Проверка столкновения с окном
  if (player.x < 0) player.x = static_cast<float>(resolutionx);
  if (player.y < 0) player.y = static_cast<float>(resolutiony);
  if (player.x > resolutionx) player.x = 0;
  if (player.y > resolutiony) player.y = 0;

  if (mouse_pressed)
     bullets(player);

  if (!shop && wawe)
    money += player.gold_passive;
}

