#include "mcs.h"

thread_local MCSNode *MCSLock::my_node = new MCSNode;

MCSLock::MCSLock() : tail(nullptr) {}

MCSLock::~MCSLock() {
  auto old_tail = tail.exchange(nullptr, std::memory_order_acq_rel);
  if (old_tail != nullptr)
    delete old_tail;
}

void MCSLock::lock() {
  // Put ourselves at the end of the queue
  auto prev = tail.exchange(my_node, std::memory_order_acq_rel);

  // If there was a previous node, wait before proceeding into the critical
  // section
  if (prev != nullptr) {
    // Mark ourselves as locked
    my_node->locked = true;
    // Link ourselves to the previous node
    prev->next.store(my_node, std::memory_order_release);

    // Wait for our predecessor to wake us
    while (my_node->locked)
      spin_loop();
  }
}

void MCSLock::unlock() {
  // Since we are holding the lock, try to get our successor
  auto next = my_node->next.load(std::memory_order_acquire);

  if (next == nullptr) {
    // Since we don't have a successor, we should be at the tail. Try to
    // remove ourselves from the queue.
    auto old_tail = my_node;
    if (tail.compare_exchange_strong(old_tail, nullptr,
                                     std::memory_order_acq_rel))
      // No successor waiting, immediately return
      return;

    // We weren't at the tail, even though we don't have a next node, meaning
    // another node has taken the tail but has not yet linked themselves
    // to us. Wait for them to link.
    while ((next = my_node->next.load(std::memory_order_relaxed)) == nullptr)
      spin_loop();
  }

  // Unlock our successor
  next->locked = false;
}
