#pragma once
#include <vector>
#include <string>
#include "potato-sfml.h"

inline bool lan_enabled = false;
inline bool is_server = false;
inline const int server_port = 35663;
inline const sf::IpAddress server_ip(26, 211, 51, 240);
inline sf::UdpSocket sock;
inline std::vector<std::string> client_commands;
inline std::vector<std::string> server_commands; // команды от сервера
inline std::optional<sf::IpAddress> client_ip;
inline unsigned short client_port;

std::string make_packet_close();
std::string make_packet_key(sf::Keyboard::Key key);
std::string make_packet_mouse(float x, float y);
std::string make_packet_obj(std::string texture, float x, float y, float scale);
std::string make_packet_money(int64_t coins);

std::vector<std::string> split_command(std::string cmd);
