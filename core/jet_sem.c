#include "jet_sem.h"

jet_int sem_get(jet_int key)
{
    jet_int semid = semget(key, 1, IPC_NOWAIT);
    if (semid != -1)
        return semid;
    else
        goto NOT_FOUND;
NOT_FOUND:
    return JET_ERROR;
}

void sem_del(jet_int key)
{
    jet_int semid = sem_get(key);
    if (semid != JET_ERROR) {
        semctl(semid, 0, IPC_RMID);
    }
}

jet_int sem_create(jet_int key)
{
    jet_int semid = semget(key, 1, IPC_CREAT|IPC_EXCL|IPC_NOWAIT|SEM_FLG_PERMS);
    if (semid == -1) {
        fprintf(stderr, "create sem failed. errno:%d\n", errno);
        exit(1);
    }

    semctl(semid, 0, SETALL);

    return semid;
}

/**************************************************test**************************************/
void sem_pre_test()
{
    jet_int semid1 = sem_create(SEM_LOG_KEY);
    jet_int semid2 = sem_get(SEM_LOG_KEY);
    sem_del(SEM_LOG_KEY);
    printf("create semid:%d, get semid:%d\n", semid1, semid2);
}