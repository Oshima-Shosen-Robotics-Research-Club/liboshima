#pragma once

#include <stddef.h>
#include <stdint.h>

inline void setup();
inline void loop();

int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}