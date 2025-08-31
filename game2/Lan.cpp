#include <string>
#include <sstream>
#include "Lan.h"

std::vector<std::string> split_command(std::string cmd) {
    std::vector<std::string> result;
    std::string param;
    std::istringstream iss;
    iss.str(cmd);

    while (std::getline(iss, param, '|'))
        result.push_back(param);

    return result;
}

std::string make_packet_close() { return "CLOSE"; }
std::string make_packet_key(sf::Keyboard::Key key) {
    return "KEY|" + sf::Keyboard::getDescription(sf::Keyboard::delocalize(key));
}
std::string make_packet_mouse(float x, float y) { return "MOUSE|" + std::to_string(x) + "|" + std::to_string(y); }

std::string make_packet_obj(std::string texture, float x, float y, float scale) {
    return "OBJ|" + texture + "|" + std::to_string(x) + "|" + std::to_string(y) + "|" + std::to_string(scale);
}

std::string make_packet_money(int64_t coins) {
    return "COIN_COUNT|" + std::to_string(coins);
}
