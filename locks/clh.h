#pragma once

#include "cache_pad.h"
#include "lock.h"
#include "spin_loop.h"
#include <atomic>

struct QNode {
  bool locked;

  QNode() : locked(false){};
} __attribute__((aligned(CACHE_LINE_SIZE)));

class CLHLock {
public:
  CLHLock();
  ~CLHLock();
  void lock();
  void unlock();

private:
  std::atomic<QNode *> tail;
  thread_local static QNode *my_node;
  thread_local static QNode *my_pred;
};
