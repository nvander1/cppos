#pragma once

#include <stdint.h>
#include <stddef.h>

namespace tty {

class Terminal {
 public:
  Terminal();
  void put_char(char ch);
  void put_string(const char* string);

 private:
  size_t make_index(size_t x, size_t y);
  void scrollup();

  size_t d_row = 0;
  size_t d_column = 0;
  volatile uint16_t* const d_buffer =
      reinterpret_cast<uint16_t*>(0xB8000);

  static size_t WIDTH;
  static size_t HEIGHT;
  static uint8_t COLOR;
};

} // namespace tty
