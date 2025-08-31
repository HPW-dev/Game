#include <sstream>
#include <iostream>
#include "Lan-menu.h"
#include "menu.h"
#include "Objects.h"
#include "Game_Core.h"
#include "Player.h"
#include "Rec.h"
#include "Font.h"
#include "Graphic.h"
#include "Button.h"
#include "Lan.h"
#include "menu-character.h"

static Button btn_server;
static Button btn_client;
static Button btn_click;
static Button btn_exit;
static bool once_init = true;

void update_lan_menu() {
	if (once_init) {
		once_init = false;
		lan_enabled = true;

		btn_server = Button {
			.text = "Server",
			.text_offset_x = 0,
			.text_offset_y = 0,
			.text_size = 60,
			.rectangle = Rectangle{resolutionx / 2, resolutiony / 2, 200, 60},
			.click_sound = "bullet_sound",
			//.texture = "player",
			.action = []{
				sock.setBlocking(false);
				if (sock.bind(server_port) != sf::Socket::Status::Done) {
                    std::cerr << "Failed to bind to port " << server_port << std::endl;
                    std::terminate();
                }
                is_server = true;
			}
		};
		/*
		btn_client = Button{
			.text = "Client",
			.text_offset_x = 0,
			.text_offset_y = 0,
			.text_size = 60,
			.rectangle = Rectangle{resolutionx / 2, resolutiony / 2 + 70, 200, 60},
			.click_sound = "bullet_sound",
			//.texture = "player",
			.action = [] {
				// ...
			}
		};
		*/
		btn_click = Button{
			.text = "Start",
			.text_offset_x = 0,
			.text_offset_y = 0,
			.text_size = 60,
			.rectangle = Rectangle{resolutionx / 2, resolutiony / 2 + 140, 200, 60},
			.click_sound = "bullet_sound",
			//.texture = "player",
			.action = [] {
                game_reset();
			}
		};
	}
    
    check(btn_server);
    //check(btn_client);
    check(btn_click);
    //check(btn_exit);
}

void render_lan_menu(sf::RenderWindow& window) {
	background = "bg_for_menu";
    draw_texture(window, background, resolutionx/2,resolutiony/2, fullscreen ? 2.f : 1.f);
	draw(window, btn_server);
	//draw(window, btn_client);
	draw(window, btn_click);
}
