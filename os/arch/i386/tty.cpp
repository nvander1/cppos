#include "tty.hpp"
#include "string.hpp"
#include "vga.hpp"
#include <cstdint>

namespace tty {

Terminal::Terminal() {
  for (auto y = 0ULL; y < HEIGHT; ++y) {
    for (auto x = 0ULL; x < WIDTH; ++x) {
      auto index = make_index(x, y);
      d_buffer[index] = vga::entry(' ', COLOR);
    }
  }
}

void Terminal::put_char(char c) {
  if (c == '\n') {
    d_column = 0;
    ++d_row;
    return;
  }

  auto index = d_row * WIDTH + d_column;
  d_buffer[index] = vga::entry(c, COLOR);
  d_column = ((1 + d_column) % WIDTH);
  if (d_column == 0) {
    ++d_row;
    if (d_row == HEIGHT) {
      --d_row;
      scrollup();
    }
  }
}

void Terminal::put_string(const char* data) {
  for (auto i = 0ULL; i < strlen(data); ++i) {
    put_char(data[i]);
  }
}

std::size_t Terminal::make_index(std::size_t x, std::size_t y) {
  return y * WIDTH + x;
}

void Terminal::scrollup() {
  for (auto y = 1ULL; y < HEIGHT; ++y) {
    for (auto x = 0ULL; x < WIDTH; ++x) {
      auto cur_index = make_index(x, y);
      auto new_index = make_index(x, y - 1);
      d_buffer[new_index] = d_buffer[cur_index];
    }
  }
  for (auto x = 0ULL; x < WIDTH; ++x) {
    auto index = make_index(x, HEIGHT - 1);
    d_buffer[index] = ' ';
  }
}

std::size_t Terminal::WIDTH = 80;
std::size_t Terminal::HEIGHT = 25;
std::uint8_t Terminal::COLOR = vga::entry_color(vga::LIGHT_GREY, vga::BLACK);

} // namespace tty
