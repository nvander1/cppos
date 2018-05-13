#include "vga.hpp"
#include <cstdint>

#ifndef __i386__
#error "need ix86 elf compiler"
#endif

void scrolling_test(vga::Terminal<>& term) {
  char line[81];
  line[80] = '\0';

  while (true) {
    for (char c = 'A'; c < 'Z'; ++c) {
      for (auto i = 0; i < 80; ++i) {
        line[i] = c;
      }
      for (auto i = 0ULL; i < 50'000'000; ++i);
      term << line;
    }
  }
}

extern "C" void kernel_main(void) {
  auto term = vga::Terminal{};

  scrolling_test(term);
}
