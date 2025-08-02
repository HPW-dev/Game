/*ƒ«:
1. подрукрутить прирост золота (побольше)+
2. hp никогда не должно быть больше чем max_hp
3. вампиризм должен лечить медленнее+
4. код нового предмета добавить (характеристики уже добавл€ютс€ игроку, надо их применить)
*/

#pragma once
#include "Game_Object.h"
#include "Objects.h"
#include <SFML/Window.hpp>
#include "Game_Core.h"
#include <iostream>
#include "Misc.h"

void makeplayer() {
  Game_Object player;
  player.type = Type::player;
	player.x = resolutionx / 2;
	player.y = resolutiony / 2;
	player.speed = 2.5;
	player.hitbox = 30;
  player.color = { 255,100,97 };
  player.hp = 100;
  player.damage = 1;
  player.max_hp = player.hp;
  player.regen = 0;
  player.gold_passive = 0;
  player.texture = "player";
  spawn(player);
}

void bullets(Game_Object& player) {
    if (player.shot_time <= 0) {
        Game_Object bullet;
        bullet.type = Type::bullet;
        bullet.x = player.x;
        bullet.y = player.y;
        bullet.speed = 6;
        bullet.hitbox = 10;
        bullet.color = { 173,255, 47 };
        float dist = distance(player.x,player.y,mousex,mousey);
        bullet.vx = (mousex - player.x) / dist*bullet.speed;
        bullet.vy = (mousey - player.y) / dist*bullet.speed;
        player.shot_time = 15;
        bullet.damage = 10;
        bullet.hp = bullet.max_hp = 100;
        bullet.creator = player.type;
        bullet.texture = "bullet";
        spawn(bullet);
        
    }
}
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
    //ѕроверка столкновени€ с окном
    if (player.x < 0) player.x = resolutionx;
    if (player.y < 0) player.y = resolutiony;
    if (player.x > resolutionx) player.x = 0;
    if (player.y > resolutiony) player.y = 0;

    if (mouse_pressed)
       bullets(player);
  
    if(shop == false)
      money += player.gold_passive; 
}
