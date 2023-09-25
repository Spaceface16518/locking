// redefine symbols of pthread_mutex api to print lock info

#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>

typedef int (*pthread_mutex_lock_t)(pthread_mutex_t *mutex);

int real_pthread_mutex_lock(pthread_mutex_t *mutex) noexcept(true) {
  return ((pthread_mutex_lock_t)dlsym(RTLD_NEXT, "pthread_mutex_lock"))(mutex);
}

extern "C" int pthread_mutex_lock(pthread_mutex_t *mutex) noexcept(true) {
  fprintf(stderr, "lock %p\n", mutex);
  return real_pthread_mutex_lock(mutex);
}

typedef int (*pthread_mutex_unlock_t)(pthread_mutex_t *mutex);

int real_pthread_mutex_unlock(pthread_mutex_t *mutex) noexcept(true) {
  return ((pthread_mutex_unlock_t)dlsym(RTLD_NEXT, "pthread_mutex_unlock"))(
      mutex);
}

extern "C" int pthread_mutex_unlock(pthread_mutex_t *mutex) noexcept(true) {
  fprintf(stderr, "unlock %p\n", mutex);
  return real_pthread_mutex_unlock(mutex);
}

typedef int (*pthread_mutex_trylock_t)(pthread_mutex_t *mutex);

int real_pthread_mutex_trylock(pthread_mutex_t *mutex) noexcept(true) {
  return ((pthread_mutex_trylock_t)dlsym(RTLD_NEXT, "pthread_mutex_trylock"))(
      mutex);
}

extern "C" int pthread_mutex_trylock(pthread_mutex_t *mutex) noexcept(true) {
  fprintf(stderr, "trylock %p\n", mutex);
  return real_pthread_mutex_trylock(mutex);
}
