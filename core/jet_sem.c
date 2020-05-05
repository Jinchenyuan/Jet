#include "jet_sem.h";

jet_int sem_get(jet_int key)
{
    jet_int semfd = semget(key, 1, SEM_FLG_CHECK);
    if (semfd != -1)
        return semfd;
    else
        goto NOT_FOUND;
NOT_FOUND:
    return JET_ERROR;
}

void sem_del(jet_int key)
{
    jet_int semfd = sem_get(key);
    if (semfd != JET_ERROR) {
        
    }

}

jet_int sem_create(jet_int key)
{
    sem_del(key);
}

/**************************************************test**************************************/
void sem_pre_test()
{
    jet_int semid = semget(SEM_LOG_KEY, 1, 0666|IPC_EXCL|IPC_CREAT);
}