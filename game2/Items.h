#pragma once
#include <vector>
#include <string>
#include <map>
struct shop_item
{
	std::string name;
	int coast;
	double movment_slowdown = 0;
	double vampirism = 0;
	double Damage_Reflection = 0;
	double resurrection = 0;
	double HP_to_damage_ratio = 0;
	double x2_coins_chance = 0;
	double passive_gold = 0;
};

std::vector <shop_item> shop_items;
std::map <std::string, shop_item> items_base{
	//Passive income + 0.1 per sec can stack
	{"Structure",shop_item{
		.name = "farm",
		.coast = 10000,
		.passive_gold = 0.1,
	} },
	//50 percent chance that the coin will give 2 times more
	{"Buff1",shop_item{
		.name = "x2 coins",
		.coast = 10000,
		.x2_coins_chance = 0.2,
	} },
	//the less health, the higher the damage
	{"Artifacts4",shop_item{
		.name = "The Martyr's Chain",
		.coast = 3000,
		.HP_to_damage_ratio = 20,
	}},
	//Vampirism
	{"Artifacts1",shop_item{
		.name = "Vampire blood ",
		.coast = 3000,
		.vampirism = 0.08,
	}},
	//Damage Reflection
	{"Artifacts2",shop_item{
		.name = "Soul Mirror Fragment",

		.coast = 3000,
		.Damage_Reflection = 8.0,
	}},
	//{"Staff1",shop_item{.name = "Icecrown Staff",.coast = 5000}},//slow
	//{"Artifacts3",shop_item{.name = "Shadow of the Phoenix",.coast = 10000}},//Resurrection 1 time
};