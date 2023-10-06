#include "clh.h"

CLHLock::CLHLock() : tail(new QNode){};

CLHLock::~CLHLock() {
  QNode *old_tail = tail.exchange(nullptr, std::memory_order_acq_rel);
  if (old_tail != nullptr)
    delete old_tail;
};

thread_local QNode *CLHLock::my_node = new QNode;
thread_local QNode *CLHLock::my_pred = nullptr;

void CLHLock::lock() {
  my_node->locked = true;

  QNode *pred = tail.exchange(my_node, std::memory_order_acq_rel);

  if (pred != nullptr) {
    my_pred = pred;
    while (pred->locked)
      spin_loop();
  }
};

void CLHLock::unlock() {
  my_node->locked = false;
  my_node = my_pred;
};
