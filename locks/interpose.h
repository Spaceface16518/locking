#pragma once

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // !_GNU_SOURCE

#include <dlfcn.h>
#include <pthread.h>

#ifndef LOCK_NAME
#error "LOCK_NAME must be defined to use this header"
#endif // !LOCK_NAME

#define PASTER(x, y) x##_##y
#define EVALUATOR(x, y) PASTER(x, y)

#define REAL(name) EVALUATOR(LOCK_NAME, name)

inline int REAL(mutex_init)(pthread_mutex_t *mutex,
                            const pthread_mutexattr_t *mutexattr);

typedef int (*pthread_mutex_init_t)(pthread_mutex_t *mutex,
                                    const pthread_mutexattr_t *mutexattr);

extern "C" int pthread_mutex_init(pthread_mutex_t *mutex,
                                  const pthread_mutexattr_t *mutexattr) {
  return REAL(mutex_init)(mutex, mutexattr);
}

inline int REAL(mutex_destroy)(pthread_mutex_t *mutex);

typedef int (*pthread_mutex_destroy_t)(pthread_mutex_t *mutex);

extern "C" int pthread_mutex_destroy(pthread_mutex_t *mutex) {
  return REAL(mutex_destroy)(mutex);
}

inline int REAL(mutex_lock)(pthread_mutex_t *mutex);

typedef int (*pthread_mutex_lock_t)(pthread_mutex_t *mutex);

extern "C" int pthread_mutex_lock(pthread_mutex_t *mutex) noexcept(true) {
  return REAL(mutex_lock)(mutex);
}

inline int REAL(mutex_unlock)(pthread_mutex_t *mutex);

typedef int (*pthread_mutex_unlock_t)(pthread_mutex_t *mutex);

extern "C" int pthread_mutex_unlock(pthread_mutex_t *mutex) noexcept(true) {
  return REAL(mutex_unlock)(mutex);
}

inline int REAL(mutex_trylock)(pthread_mutex_t *mutex);

typedef int (*pthread_mutex_trylock_t)(pthread_mutex_t *mutex);

extern "C" int pthread_mutex_trylock(pthread_mutex_t *mutex) noexcept(true) {
  return REAL(mutex_trylock)(mutex);
}
