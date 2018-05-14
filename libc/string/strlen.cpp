#include <string.h>

std::size_t strlen(const char* str) {
  auto len = 0ULL;
  while (str[len]) {
    ++len;
  }
  return len;
}
