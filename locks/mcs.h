#pragma once

#include "spin_loop.h"
#include <atomic>

struct MCSNode {
  bool locked;
  std::atomic<MCSNode *> next;

  MCSNode() : locked(false), next(nullptr) {}
};

class MCSLock {
public:
  MCSLock();
  ~MCSLock();
  void lock();
  void unlock();

private:
  std::atomic<MCSNode *> tail;

  thread_local static MCSNode *my_node;
};
