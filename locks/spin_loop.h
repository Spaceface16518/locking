#pragma once

static inline void spin_loop() {
#if (COMPILER == GCC || COMPILER == CLANG)
  asm volatile("pause\n" : : : "memory");
#endif
}
