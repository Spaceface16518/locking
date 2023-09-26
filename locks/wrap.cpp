#define LOCK_NAME wrap
#include "interpose.h"

#include <dlfcn.h>
#include <pthread.h>

int REAL(mutex_init)(pthread_mutex_t *mutex,
                     const pthread_mutexattr_t *mutexattr) {
  return ((pthread_mutex_init_t)dlsym(RTLD_NEXT, "pthread_mutex_init"))(
      mutex, mutexattr);
}

int REAL(mutex_destroy)(pthread_mutex_t *mutex) {
  return ((pthread_mutex_destroy_t)dlsym(RTLD_NEXT, "pthread_mutex_destroy"))(
      mutex);
}

int REAL(mutex_lock)(pthread_mutex_t *mutex) {
  return ((pthread_mutex_lock_t)dlsym(RTLD_NEXT, "pthread_mutex_lock"))(mutex);
}

int REAL(mutex_unlock)(pthread_mutex_t *mutex) {
  return ((pthread_mutex_unlock_t)dlsym(RTLD_NEXT, "pthread_mutex_unlock"))(
      mutex);
}

int REAL(mutex_trylock)(pthread_mutex_t *mutex) {
  return ((pthread_mutex_trylock_t)dlsym(RTLD_NEXT, "pthread_mutex_trylock"))(
      mutex);
}
