#include "Button.h"
#include "Font.h"
#include "Sound.h"
#include "Graphic.h"
#include "Game_Core.h"

bool check(Button& btn) {
    if (mouse_pressed == false)
        return false;

	if (in_Rectangle(btn.rectangle, static_cast<int>(mousex), static_cast<int>(mousey))) {
		if (btn.action)
            btn.action();
        if (btn.click_sound.empty() == false)
            play_sound(btn.click_sound);
        return true;
	}

    return false;
}

void draw(sf::RenderWindow& wnd, const Button& btn) {
    if (btn.texture.empty() == false)
        draw_texture(wnd, btn.texture, btn.rectangle.x, btn.rectangle.y, btn.texture_size, false);

    if (btn.text.empty() == false)
        drawtxt(wnd, btn.text,
            btn.rectangle.x + btn.text_offset_x,
            btn.rectangle.y + btn.text_offset_y,
            btn.text_size);
}
