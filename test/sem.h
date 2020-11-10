#ifndef _TEST_SEM_H_
#define _TEST_SEM_H_

#include "../core/jet_sem.h"
/**************************************************test**************************************/
void sem_pre_test()
{
    jet_int semid1 = sem_create(SEM_LOG_KEY);
    jet_int semid2 = sem_get(SEM_LOG_KEY);
    sem_del(SEM_LOG_KEY);
    printf("create semid:%d, get semid:%d\n", semid1, semid2);
}

#endif