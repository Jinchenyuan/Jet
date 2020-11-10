#include "jet_define.h"
#include "jet_thread.h"
#include "jet_lock.h"

void create_thread(pthread_t *t, void *(*start_routine)(void *), void *arg)
{
    if (pthread_create(t, NULL, start_routine, arg)) {
        fprintf(stderr, "create thread failed.\n");
        exit(1);
    }
}