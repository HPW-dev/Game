#pragma once
struct Rectangle
{
	int x, y;
	int max_x, max_y;
};
bool in_Rectangle(Rectangle rec,int x,int y) {
	if (rec.x < x && x < rec.x+rec.max_x && rec.y < y && y < rec.y + rec.max_y)
	{
		return true;
	}
	return false;
}