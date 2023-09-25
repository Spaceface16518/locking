#include <pthread.h>

int main() {
  // simple demo of pthread_mutex library to test the interposed wrapper
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_lock(&mutex);
  pthread_mutex_unlock(&mutex);
  pthread_mutex_destroy(&mutex);
  return 0;
}
