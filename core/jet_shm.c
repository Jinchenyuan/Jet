#include "jet_shm.h"
#include <sys/sem.h>

static inline void shm_init(jet_int shmfd, jet_int size)
{
    jet_int *p = (jet_int*)shmat(shmfd, NULL, 0);

    *p = size;
    *++p = sizeof(jet_int) * 3 + 1;
    *++p = sizeof(jet_int) * 3 + 1;
}

static inline void shm_to_begin(int **p)
{
    jet_int begin = *(++*p);
    (*p) += (begin - (sizeof(jet_int) + 1));
}

static inline jet_int shm_insert_overflow(int *p, jet_int size)
{


    return JET_OK;
}

jet_int shm_get(jet_int key)
{
    jet_int shmfd = shmget(key, GET_SIZE_BY_KEY(key), SHM_FLG_CHECK);
    if (shmfd != -1)
        return shmfd;
    else
        goto NOT_FOUND;

NOT_FOUND:
    return JET_ERROR;
}

void shm_del(jet_int key)
{
    jet_int shmfd = shm_get(key);
    printf("del shmfd:%d\n", shmfd);
    if (shmfd != JET_ERROR) {
        void *addr = shmat(shmfd, NULL, 0);
        if (addr != (void *)-1)
        {
            shmdt(addr);
            shmctl(shmfd, IPC_RMID, 0) ;
        }
    }
}

jet_int shm_create(jet_int key, jet_uint size)
{
    jet_int shmfd = shm_get(key);
    if (shmfd != JET_ERROR) {
        void *addr = shmat(shmfd, NULL, 0);
        if (addr != (void *)-1)
        {
            shmdt(addr);
            shmctl(shmfd, IPC_RMID, 0) ;
        }
    }
    
    shmfd = shmget(key, size, SHM_FLG_CHECK|IPC_CREAT|IPC_EXCL);
    if (shmfd == -1) {
        fprintf(stderr, "create shm failed. errno:%d\n", errno);
        exit(1);
    }

    shm_init(shmfd, size);

    return shmfd;
}

void shm_write(jet_int shmfd, shmchunk *sc)
{
    jet_int *p = (jet_int*)shmat(shmfd, NULL, 0);
    assert((shm_insert_overflow(p, sc->size) == JET_OK));
    shm_to_begin(&p);
    printf("pos:%d\n", *p);
}

shmchunk* shm_read(jet_int shmfd)
{
    return NULL;
}

void shm_pre_test()
{
    jet_int shmfd = shm_create(SHM_LOG_KEY, SHM_LOG_SIZE);
    printf("shmfd:%d\n", shmfd);
    shmchunk sc;
    sc.size = 8;
    sc.data = NULL;
    shm_write(shmfd, &sc);
    shm_del(SHM_LOG_KEY);
}