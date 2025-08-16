#pragma once
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "Game_Object.h"
#include "Game_Core.h"
#include "dps-numbers.h"

struct shop_item {
	std::string name{};
	int coast{};
	bool buy = false;
	std::function<void (Game_Object&)> action {}; // действие при покупке
};

constexpr int BASE_COAST = 18'500;

inline std::vector <shop_item> shop_items;
inline std::map <std::string, shop_item> items_base{
	//Passive income + 0.1 per sec can stack
	{"Structure",shop_item{
		.name = "farm",
		.coast = int(BASE_COAST * 1.1),
		.action = [](Game_Object& player) {
			player.gold_passive += 0.35f;
			add_label(200, 200, "PASSIVE GOLD " + std::to_string(player.gold_passive), sf::Color::White);
		}
	} },
	//50 percent chance that the coin will give 2 times more
	{"Buff1",shop_item{
		.name = "x2 coins",
		.coast = int(BASE_COAST * 0.7),
		.action = [](Game_Object& player) {
			player.x2_gold += 0.2f;
			add_label(200, 200, "x2 GOLD " + std::to_string(player.x2_gold), sf::Color::White);
		}
	} },
	{"art-coast",shop_item{
		.name = "Coast +70%",
		.coast = int(BASE_COAST * 0.5),
		.action = [](Game_Object& player) {
			player.coast_plus += 0.75f;
			add_label(200, 200, "COAST + " + std::to_string(player.coast_plus), sf::Color::White);
		}
	} },
	//the less health, the higher the damage
	{"Artifacts4",shop_item{
		.name = "The Martyr's Chain",
		.coast = int(BASE_COAST * 0.3),
		.action = [](Game_Object& player) {
			player.HP_to_damage_ratio += 3.f;
			add_label(200, 200, "HP/DAMAGE " + std::to_string(player.HP_to_damage_ratio), sf::Color::White);
		}
	}},
	//Vampirism
	{"Artifacts1",shop_item{
		.name = "Vampire blood ",
		.coast = int(BASE_COAST * 0.9),
		.action = [](Game_Object& player) {
			player.vampirism += 0.18f;
			add_label(200, 200, "VAMPIRISM " + std::to_string(player.vampirism), sf::Color::White);
		}
	}},
	//Damage Reflection
	{"Artifacts2",shop_item{
		.name = "Soul Mirror Fragment",
		.coast = int(BASE_COAST * 0.9),
		.action = [](Game_Object& player) {
			player.damage *= 8.0f;
			add_label(200, 200, "DAMAGE REFLECTION " + std::to_string(int(player.damage)), sf::Color::White);
		}
	}},
	//slow
	{"Staff1",shop_item{
		.name = "Icecrown Staff",
		.coast = int(BASE_COAST * 0.2),
		.action = [](Game_Object& player) {
			player.movement_slowdown += 0.1f;
			add_label(200, 200, "ENEMY SLOWDOWN " + std::to_string(player.movement_slowdown), sf::Color::White);
		}
	}},
	//Resurrection 1 time
	/*{"Artifacts3",shop_item{
		.name = "Shadow of the Phoenix",
		.coast = int(BASE_COAST * 1.4),
		.action = [](Game_Object& player) {
			player.resurections += 1;
			add_label(200, 200, "RESURECTIONS " + std::to_string(player.resurections), sf::Color::White);
		}
	}},*/
	{"art-size",shop_item{
		.name = "Size +33%",
		.coast = int(BASE_COAST * 0.666),
		.action = [](Game_Object& player) {
			player.size += 1.f / 3.f;
			add_label(200, 200, "SIZE + " + std::to_string(int(player.size)), sf::Color::White);
		}
	}},
	{"art-size-minus",shop_item{
		.name = "Size -10%",
		.coast = int(BASE_COAST * 0.75),
		.action = [](Game_Object& player) {
			player.size = std::max(0.01f, player.size * 0.9f);
			add_label(200, 200, "SIZE - " + std::to_string(int(player.size)), sf::Color::White);
		}
	}},
	{"art-damage",shop_item{
		.name = "Damage +50%",
		.coast = int(BASE_COAST * 0.3),
		.action = [](Game_Object& player) {
			player.damage += 0.5f;
			add_label(200, 200, "DAMAGE + " + std::to_string(int(player.damage)), sf::Color::White);
		}
	}},
	{"art-max-hp",shop_item{
		.name = "Max HP +150%",
		.coast = int(BASE_COAST * 0.6),
		.action = [](Game_Object& player) {
			player.max_hp += player.max_hp * 1.5f;
			player.hp += player.hp * 1.5f;
			add_label(200, 200, "MAX HP " + std::to_string(int(player.max_hp)), sf::Color::White);
		}
	}},
	{"art-maxhp-to-damage",shop_item{
		.name = "30% HP -> 90% damage",
		.coast = int(BASE_COAST * 0.2),
		.action = [](Game_Object& player) {
			player.max_hp *= 0.666f;
			player.damage *= 1.9f;
			add_label(200, 200, "MAX HP " + std::to_string(int(player.max_hp)), sf::Color::Red);
			add_label(200, 300, "DAMAGE " + std::to_string(int(player.damage)), sf::Color::Green);
		}
	}},
	{ "art-speedup",shop_item{
		.name = "Speed +15%",
		.coast = int(BASE_COAST * 0.4),
		.action = [](Game_Object& player) {
			player.speed *= 1.15f;
			add_label(200, 200, "SPEED " + std::to_string(int(player.speed)), sf::Color::Green);
		}
	} },
	{ "art-shoot-speedup",shop_item{
		.name = "Shoot speed +20%",
		.coast = int(BASE_COAST * 0.666f),
		.action = [](Game_Object& player) {
			player.shot_time_max *= 0.80f;
			add_label(200, 200, "SHOOT DELAY " + std::to_string(int(player.shot_time_max)), sf::Color::Green);
		}
	} },
	{ "art-armor",shop_item{
		.name = "Armor +20%",
		.coast = int(BASE_COAST * 0.85f),
		.action = [](Game_Object& player) {
			player.armor += 0.2f;
			add_label(200, 200, "ARMOR " + std::to_string(int(player.armor)), sf::Color::Green);
		}
	} },
	{ "art-coing-to-hp",shop_item{
		.name = "Coin -> HP",
		.coast = int(BASE_COAST * 0.9f),
		.action = [](Game_Object& player) {
			player.coin_to_hp += 1.5f;
			add_label(200, 200, "COIN TO HP " + std::to_string(int(player.armor)), sf::Color::Green);
		}
	} },
	{ "art-bullets-up",shop_item{
		.name = "Bullets x2",
		.coast = int(BASE_COAST * 1.5f),
		.action = [](Game_Object& player) {
			player.bullets *= 2;
			add_label(200, 200, "BULLETS " + std::to_string(player.bullets), sf::Color::Green);
		}
	} },
	{ "art-air",shop_item{
		.name = "Air",
		.coast = 0,
	} },
	{ "art-rich",shop_item{
		.name = "Rich",
		.coast = int(BASE_COAST * 5.f),
		.action = [](Game_Object& player) {
			money += BASE_COAST * 7.5f;
			add_label(200, 200, "MONEY " + std::to_string(int(money)), sf::Color::Green);
		}
	} },
	{ "art-error",shop_item{
		.name = "Error",
		.coast = -1,
		.action = [](Game_Object& player) {
			std::terminate();
		}
	} },
	
	{ "art-casino",shop_item{
		.name = "Casino",
		.coast = int(BASE_COAST * 0.6f),
		.action = [](Game_Object& player) {
			if (rand() % 2) {
				money *= 4.f;
				add_label(200, 200, "MONEY +" + std::to_string(int(money)), sf::Color::Green);
			} else {
				money *= -1;
				add_label(200, 200, "MONEY -" + std::to_string(int(money)), sf::Color::Red);
			}
		}
	} },
};