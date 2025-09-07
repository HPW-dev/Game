#include "menu-game.h"
#include "Game_Core.h"
#include "Bot1.h"
#include "Bot2.h"
#include "Boss.h"
#include "Graphic.h"
#include "Game_object_control.h"
#include "Menu.h"
#include "Misc.h"
#include "Objects.h"
#include "dps-numbers.h"
#include "Lan.h"

/*
КОМАНДА|ПАРАМЕТРЫ|...
OBJ|НАЗВАНИЕ_ТЕКСТУРЫ|КООРДИНАТА_X|КООРДИНАТА_Y|РАЗМЕР
BG|НАЗВАНИЕ_ТЕКСТУРЫ
TXT|ДАННЫЕ|КООРДИНАТА_X|КООРДИНАТА_Y|РАЗМЕР
EXIT - ВЫХОД КЛИЕНТА ИЗ ИГРЫ
ENEMY_COUNT|КОЛВО ПРОТИВНИКОВ
COIN_COUNT|КОЛВО МОНЕТ
*/

static void update_client(const sf::IpAddress& client_ip, unsigned short client_port) {
	sf::Packet packet;

	for (auto& obj : objects)
		packet << make_packet_obj(obj.texture, obj.x, obj.y, obj.size);

	packet << make_packet_money((int64_t)money);
	packet << "BG|" + background;
	packet << "DRAW_TXT|" + std::to_string(int(objects[0].hp)) + "|" + std::to_string(objects[0].x) + "|" + std::to_string(objects[0].y - 50) + "|10";
	packet << "DRAW_TXT|" + std::to_string(int(objects[1].hp)) + "|" + std::to_string(objects[1].x) + "|" + std::to_string(objects[1].y - 50) + "|10";
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) packet << "EXIT";

	sock.send(packet, client_ip, client_port);
}
static void process_lan() {
	client_commands.clear();
	sf::Packet packet;

	if (is_server) {
		std::string cmd;
		std::optional<sf::IpAddress> ip;
		unsigned short port;

		if (sock.receive(packet, ip, port) == sf::UdpSocket::Status::Done) {
			while (packet >> cmd)
				client_commands.push_back(cmd);
		
			if (ip) {
				client_ip = ip;
				client_port = port;
			}
		}
		
		if (client_ip)
			update_client(*client_ip, client_port);
	} else { // client
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) packet << make_packet_key(sf::Keyboard::Key::W);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) packet << make_packet_key(sf::Keyboard::Key::S);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) packet << make_packet_key(sf::Keyboard::Key::A);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) packet << make_packet_key(sf::Keyboard::Key::D);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) packet << make_packet_close();
		if (mouse_pressed) packet << make_packet_mouse(mousex, mousey);
		assert(server_ip);
		sock.send(packet, *server_ip, server_port);

		packet = {};
		std::optional<sf::IpAddress> ip;
		unsigned short port;
		server_commands.clear();

		if (sock.receive(packet, ip, port) == sf::UdpSocket::Status::Done) {
			std::string cmd;
			while (packet >> cmd)
				server_commands.push_back(cmd);
		}
	}
}

void update_game_scene() {
	if (lan_enabled)
		process_lan();

	// проверка выхода с клиента
	if (lan_enabled && is_server)
		for (const auto& cmd: client_commands)
			if (cmd == "CLOSE")
				next_menu(menu_Type::basic_menu);

	if (lan_enabled && is_server == false)
		return;
	
	// добавить объекты из очереди для спавна:
	spawn_processing();

	game_master();
	update_dps_numbers();

	// спавним врагов, пока не в магазине
	if (game_time % 150 == 0)
		if (wawe == true && shop == false) {
			// спавнить ещё больше врагов
			const int count = std::ceil(1 + (difficulty / 4) * 2);
			for (int i = 0; i < count; ++i)
				makebot1();

			// второй вид противника
			if (difficulty >= 6.0f)
				for (int i = 0; i < count; ++i)
					make_bot_2();
		}

	if (kill_boss && !boss_spawned) {
		boss_spawned = true;
		make_boss();
	}

	// физика объектов
	for (auto& object : objects)
		game_object_control(object);

	// проверка столкновений
	if (objects.size() > 1)
		for (int a = 0; a < objects.size() - 1; ++a)
			for (int b = a; b < objects.size(); ++b)
				if (&objects[a] != &objects[b])
					if (collision_filter(objects[a], objects[b]))
						if (circles_collide(objects[a], objects[b]) == true)
							damage(objects[a], objects[b]);

	// если волна кончилась, можно идти в магаз
	if (!objects.empty()) {
		auto& player = get_player();
		if (player.x >= resolutionx - 10 && wawe == false)
			next_menu(menu_Type::shop);
	}

	// смерть объектов
	std::erase_if(objects, [](Game_Object& obj) {
		bool hp_zero = obj.hp <= 0;
		// применение воскрешения
		if (obj.resurections > 0) {
			obj.resurections -= 1;
			obj.hp = obj.max_hp;
			std::cout << "Resurected!\n";
			return false;
		}
		// запуск функций при смерти объекта
		if (obj.dead_function && hp_zero == true) {
			obj.dead_function(obj);
			hp_zero = obj.hp <= 0;
		}
		return hp_zero;
	});
}

// код для графона у клиента
static void client_render(sf::RenderWindow& window) {
	draw_texture(window, background, resolutionx / 2, resolutiony / 2, fullscreen ? 2.f : 1.f);
	for (const auto& cmd : server_commands) {
		auto params = split_command(cmd);

		if (params.at(0) == "EXIT")
			next_menu(menu_Type::basic_menu);
		if (params.at(0) == "BG")
			background = params.at(1);
		if (params.at(0) == "DRAW_TXT") {
			auto txt = params.at(1);
			auto x = std::stod(params.at(2));
			auto y = std::stod(params.at(3));
			auto size = std::stod(params.at(4));
			drawtxt(window, txt, x, y, size);
		}

		// OBJ|НАЗВАНИЕ_ТЕКСТУРЫ|КООРДИНАТА_X|КООРДИНАТА_Y|РАЗМЕР
		if (params.at(0) == "OBJ") {
			auto texture = params.at(1);
			auto x = std::stod(params.at(2));
			auto y = std::stod(params.at(3));
			auto size = std::stod(params.at(4));
			draw_texture(window, texture, x, y, size);
		}

		// COIN_COUNT|КОЛВО МОНЕТ
		if (params.at(0) == "COINT_COUNT")
			drawtxt(window, params.at(1), 5, 90, 30);
	}
}

void render_game_scene(sf::RenderWindow& window) {
	window.clear();

	if (lan_enabled && !is_server) {
		client_render(window);
		return;
	}

	draw_texture(window, background, resolutionx/2,resolutiony/2, fullscreen ? 2.f : 1.f);
	std::string txt = "difficulty " + std::to_string(difficulty);
	std::string healt = "hp " + std::to_string(int(get_player().hp));
	std::string enemy_count = "enemy count " + std::to_string(enemy_info());
	std::string coin_count = "coincount " + std::to_string((int64_t)money);
	drawtxt(window, coin_count, 5, 90, 30);
	drawtxt(window, enemy_count, 5, 50, 30);
	drawtxt(window, txt, 5, 25, 20);
	drawtxt(window, healt, resolutionx - 100.f, 5, 20);
	drawtxt(window, std::to_string(game_time / 200), resolutionx - 100.f, 25, 20);
	for (auto& object : objects) {
		if (!draw_texture(window, object.texture, object.x, object.y, object.size))
			rendercircle(window, object.x, object.y, object.hitbox * object.size, object.color);
		if (!object.nick.empty())
			drawtxt(window, object.nick, object.x, object.y-50, 20);
	}
	draw_dps_numbers(window);
}
