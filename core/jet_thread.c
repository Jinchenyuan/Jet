#include "jet_define.h"
#include "jet_thread.h"
#include "jet_lock.h"

static jet_int share = 0;
spinlock lock;
void create_thread(pthread_t *t, void *(*start_routine)(void *), void *arg)
{
    if (pthread_create(t, NULL, start_routine, arg)) {
        fprintf(stderr, "create thread failed.\n");
        exit(1);
    }
}


void* thread_func1(void *argv)
{
    for (;;) {
        sleep(1);
    }
    
    jet_int i = 0;
    for (i = 0; i < 100000000; i++)
    {
        spin_lock(&lock);
        share++;
        if (100000 == share) {
            printf("share == 100000.\n");
        }
        spin_unlock(&lock);
        fprintf(stderr, (char*)argv, "\n");
        sleep(1);
    }
    
    return NULL;
}

void* thread_func2(void *argv)
{
    jet_int i = 0;
    pause();
    for(i = 0; i < 100000000; i++) {
        // fprintf(stderr, (char*)argv, "\n");
        spin_lock(&lock);
        share++;
        if (100000 == share) {
            printf("share == 100000.\n");
        }
        spin_unlock(&lock);
        // sleep(1);
    }
    return NULL;
}

void* thread_func3(void *argv)
{
    sleep(2);
    // fprintf(stderr, (char*)argv, "\n");
    jet_int i = 0;
    for (i = 0; i < 99; i++)
    {
        spin_lock(&lock);
        share++;
        if (100000 == share) {
            printf("share == 100000.\n");
        }
        spin_unlock(&lock);
    }
    return NULL;
}

void thread_test()
{
    lock.lock = 0;
    pthread_t pts[3];
    
    create_thread(&pts[0], thread_func1, "func1");
    create_thread(&pts[1], thread_func2, "func2");
    create_thread(&pts[2], thread_func3, "func3");
    int i = 0;
    for (i = 0; i < 3; i++)
    {
       pthread_join(pts[i], NULL);
    }
    printf("thread over, share:%d\n", share);
}