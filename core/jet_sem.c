#include "jet_sem.h";


void sem_pre_test()
{
    jet_int semid = semget(SEM_LOG_KEY, 1, 0666|IPC_EXCL|IPC_CREAT);
}