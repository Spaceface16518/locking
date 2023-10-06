#include "locks/clh.h"
#include "locks/mcs.h"
#include <cassert>
#include <iostream>
#include <mutex>
#include <omp.h>
#include <thread>

int main() {
  const size_t INCS = 100;

  {
    CLHLock mutex;
    int value = 0;
#pragma omp parallel for
    for (size_t i = 0; i < INCS; ++i) {
      std::lock_guard<CLHLock> locked(mutex);
      ++value;
    }

    std::lock_guard<CLHLock> locked(mutex);
    std::cout << value << std::endl;
    assert(value == INCS);
  }

  {
    MCSLock mutex;
    int value = 0;

#pragma omp parallel for
    for (size_t i = 0; i < INCS; ++i) {
      std::lock_guard<MCSLock> locked(mutex);
      ++value;
    }

    std::lock_guard<MCSLock> locked(mutex);
    std::cout << value << std::endl;
    assert(value == INCS);
  }

  return 0;
}
