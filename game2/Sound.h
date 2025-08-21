#pragma once
#include <string>

void load_sound(const std::string& name, const std::string& path, bool is_music=false);
void play_sound(const std::string& name, float volume=100.f, float pitch=1.f, bool infinity=false);
