#include <iostream>
#include <vector>
#include "menu-character.h"
#include "menu.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Player.h"
#include "Rec.h"
#include "Font.h"
#include "Graphic.h"
#include "Button.h"
#include "Lan.h"

// сброс игры
void game_reset() {
	next_menu(menu_Type::game_scene);
    objects.clear();
    difficulty = 1;
    difficulty_max = difficulty_max_default;
    difficulty_for_boss_max = DEFAULT_DIFFICULTY_FOR_BOSS;
    money = 0;
    makeplayer();

    if (lan_enabled)
        makeplayer(true);
}

static std::vector<Button> buttons {};
static bool first_start = true;

Button make_char_button(int x, int y, int char_num) {
    std::vector<std::string> chars {
        "Mage",
        "A",
        "B",
        "C",
        "100",
        "200",
        "$$$",
        "Test",
    };

    return Button {
        .text = chars[char_num % chars.size()],
        .text_offset_x = 20,
        .text_offset_y = 110,
        .text_size = 30,
        .rectangle = Rectangle{50 + x * 150, 50 + y * 200, 100, 100},
        .click_sound = "bullet_sound",
        .texture = "player",
        .action = []{
            lan_enabled = false;
            game_reset();
            first_start = true;
        }
    };
}

static void make_buttons() {
    const int table_x = 4;
    const int table_y = 3;

    int char_num = 0;
    for (int y = 0; y < table_y; ++y)
    for (int x = 0; x < table_x; ++x) {
        buttons.push_back(make_char_button(x, y, char_num));
        ++char_num;
    }

    first_start = false;
}

void update_character() {
    lan_enabled = false;
    
    if (first_start)
        make_buttons();
    for (auto& btn: buttons) {
	    if (check(btn))
            break;
    }
}

void render_character(sf::RenderWindow& window) {
	background = "bg_for_menu";
	draw_texture(window, background, resolutionx/2,resolutiony/2, fullscreen ? 2.f : 1.f);
	
    for (auto& btn: buttons)
	    draw(window, btn);
}
