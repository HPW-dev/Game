#pragma once
#include "Game_Object.h"

void makeplayer(bool lan_player=false, const std::string& char_name={});
void moveplayer(Game_Object& player);
Game_Object& get_player();
