#include "Sound.h"
#include <map>
#include <memory>
#include <stdexcept>
#include <SFML/Audio.hpp>

struct Sound {
    std::shared_ptr<sf::SoundBuffer> buf {};
    std::shared_ptr<sf::Sound> snd {};
    std::shared_ptr<sf::Music> mus {};
};

std::map<std::string, Sound> sounds;

void load_sound(const std::string& name, const std::string& path, bool is_music) {
    try {
        if (is_music) {
            
            sounds[name] = Sound {
                .mus = std::make_shared<sf::Music>(path),
            };
        } else {
            auto buf = std::make_shared<sf::SoundBuffer>(path);
            sounds[name] = Sound {
                .buf = buf,
                .snd = std::make_shared<sf::Sound>(*buf),
            };
        }
    } catch (...) {
        throw std::runtime_error("error while loading sound \"" + path + "\"");
    }
}

void play_sound(const std::string& name, float volume, float pitch, bool infinity) {
    try {
        auto& sound = sounds.at(name);
        if (sound.mus) {
            sound.mus->setVolume(volume);
            sound.mus->setPitch(pitch);
            sound.mus->play();
        } else {
            sound.snd->setVolume(volume);
            sound.snd->setPitch(pitch);
            sound.snd->play();
        }
    } catch (...) {
        throw std::runtime_error("error while playing sound \"" + name + "\"");
    }
}
