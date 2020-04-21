#include "jet_define.h"
#include "jet_thread.h"


void create_thread(pthread_t *t, void *(*start_routine)(void *), void *arg)
{
    if (pthread_create(t, NULL, start_routine, arg)) {
        fprintf(stderr, "create thread failed.\n");
        exit(1);
    }
}


void* thread_func1(void *argv)
{
    fprintf(stderr, (char*)argv, "\n");
    return NULL;
}

void* thread_func2(void *argv)
{
    for(;;) {
        fprintf(stderr, (char*)argv, "\n");
        sleep(1);
    }
    return NULL;
}

void* thread_func3(void *argv)
{
    sleep(10);
    fprintf(stderr, (char*)argv, "\n");
    return NULL;
}

void thread_test()
{
    pthread_t pts[3];
    
    create_thread(&pts[0], thread_func1, "func1");
    create_thread(&pts[1], thread_func2, "func2");
    create_thread(&pts[2], thread_func3, "func3");
    int i = 0;
    for (i = 0; i < 3; i++)
    {
       pthread_join(pts[i], NULL);
    }
}