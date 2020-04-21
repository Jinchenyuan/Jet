#ifndef __JET_THREAD_H_
#define __JET_THREAD_H_

#include <pthread.h>
#include <unistd.h>

void create_thread(pthread_t *t, void *(*start_routine)(void *), void *arg);

void thread_test();

#endif /*__JET_THREAD_H_*/