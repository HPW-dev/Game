#pragma once
#include "Bullet.h"
#include "Game_Core.h"

void move_bullet(Game_Object& object) {
	object.x += object.vx;
	object.y += object.vy;
	if (object.x<0 || object.x>resolutionx)
		object.hp = 0;
	if (object.y<0 || object.y>resolutiony)
		object.hp = 0;
}
