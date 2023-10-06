#define LOCK_NAME mcs
#include "interpose.h"

#include <pthread.h>

struct MCSNode {
  MCSNode *next;
  bool locked;
};

thread_local MCSNode *my_node = new MCSNode;

int REAL(mutex_init)(pthread_mutex_t *mutex,
                     const pthread_mutexattr_t *mutexattr) {

}