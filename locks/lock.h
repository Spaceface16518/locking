#pragma once

class Lock {
public:
  Lock();
  ~Lock();
  void lock();
  bool try_lock();
  void unlock();
};
