#pragma once
#include "Game_Object.h"
#include "Player.h"
#include "Bot1.h"
#include "Bullet.h"

inline void game_object_control(Game_Object& object) {
	switch (object.type) {
	  case Type::player: moveplayer(object); break;
	  case Type::bot1: move_bot(object); break;
	  case Type::bullet: move_bullet(object); break;
		case Type::coin: break;
	}

	// ������ �� �������
	if (object.life_time > 0) {
		object.life_time -= 1;

		if (object.life_time <= 0)
			object.hp = 0;
	}

	// �����������
	object.hp += object.regen;

	// ����� �� ����� ������
	object.hp = std::min(object.hp, object.max_hp);
}