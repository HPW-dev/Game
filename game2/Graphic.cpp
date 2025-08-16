#include <map>
#include <memory>
#include "Graphic.h"

struct Texture {
    std::shared_ptr<sf::Texture> tex {};
    std::shared_ptr<sf::Sprite> spr {};
};

std::map<std::string, Texture> textures;

void load_texture(std::string name, std::string file) {
    auto tex = std::make_shared<sf::Texture>(file);
    textures[name] = Texture {
        .tex = tex,
        .spr = std::make_shared<sf::Sprite>(*tex),
    };
}

bool draw_texture(sf::RenderWindow& window, std::string name, float x, float y, float scale) {
    try {
        auto& texture = textures.at(name);
        auto sz = texture.tex->getSize();
        texture.spr->setPosition(sf::Vector2f{x-sz.x*scale/2, y-sz.y*scale/2});
        texture.spr->setScale(sf::Vector2f{scale, scale});
        // TODO scale
        window.draw(*texture.spr);
        return true;
    } catch (...) {}

    return false;
}
