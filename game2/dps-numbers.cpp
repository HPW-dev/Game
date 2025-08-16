#include "dps-numbers.h"

// список надписей с уроном на экране
static std::vector<Dps_number> dps_numbers{};

// добавить надпись об уроне
void add_dps_number(float x, float y, float damage) {
  if (damage < 1)
    return;
  Dps_number title;
  title.pos.x = x;
  title.pos.y = y;
  title.number = std::to_string(int(damage));
  title.color = sf::Color(255, 64, 64);
  dps_numbers.push_back(title);
}

void add_label(float x, float y, std::string text, sf::Color color) {
  if (text.empty())
    return;
  Dps_number title;
  title.pos.x = x;
  title.pos.y = y;
  title.number = text;
  title.color = color;
  dps_numbers.push_back(title);
}

void draw_dps_numbers(sf::RenderWindow& wnd) {
  static size_t state; // для оптимизации миганием надписи
  size_t blink_max = 1 + (dps_numbers.size() / 40);

  for (size_t i = 0; const auto & title : dps_numbers) {
    if ((state + i) % blink_max == 0)
      drawtxt(wnd, title.number, title.pos.x, title.pos.y, 24, title.color);
    ++i;
  }

  ++state;
}

void update_dps_numbers() {
  for (auto& title : dps_numbers) {
    title.lifetime--;
    title.pos.y -= 0.2f; // двигать надпись вверх
    title.pos.x += (rand() % 3 - 1) * 0.3f;
  }
  // убить все надписи, у которых кончилось время
  std::erase_if(dps_numbers, [](Dps_number& title) {
    return title.lifetime <= 0;
    });
}
