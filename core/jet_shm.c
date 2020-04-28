#include "jet_shm.h"

static inline void shm_init(jet_int shmfd, jet_int size)
{
    jet_int *p = (jet_int*)shmat(shmfd, NULL, 0);

    *p = size;
    *++p = sizeof(jet_int) * 3 + 1;
    *++p = sizeof(jet_int) * 3 + 1;
}

static inline void shm_to_begin(jet_int **p)
{
    jet_int begin = *(++*p);
    (*p) += (begin - (sizeof(jet_int) + 1));
}

static inline void shm_end_move(jet_int *p, jet_int size)
{
    jet_int msize = *p++;
    jet_int end = *(++p);
    *p = (end + size) > msize ? (end + size) - msize + sizeof(jet_int) * 3: (end + size);
}

static inline void shm_begin_move(jet_int *p, jet_int size)
{
    jet_int msize = *p++;
    jet_int begin = *p;
    *p = (begin + size) > msize ? (begin + size) - msize + sizeof(jet_int) * 3: (begin + size);
}

static inline jet_int shm_data_exist(jet_int *p)
{
    jet_int begin = *(++p);
    jet_int end = *(++p);
    return begin != end ? JET_OK : JET_ERROR;
}

/**
 * p:       shared memory identifier
 * size:    insert to shared memory size of byte
*/
jet_int shm_insert_overflow(jet_int *p, jet_int size)
{
    jet_int msize = *p++;
    jet_int begin = *p++;
    jet_int end = *p;
    if (end >= begin) {
        if (size > msize - end + begin - sizeof(jet_int) * 3) {
            goto OVERFLOW;
        }
    }
    else {
        if (size > begin - end) {
            goto OVERFLOW;
        }
    }
    return JET_OK;

OVERFLOW:
    return JET_ERROR;
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
    shm_del(key);

    jet_int shmfd = shm_get(key);
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
    jet_int *kp = p;
    assert((shm_insert_overflow(p, sc->size + sizeof(sc->size)) == JET_OK));

    shm_to_begin(&p);

    *p++ = sc->size;
    memcpy(p, sc->data, sc->size);

    shm_end_move(kp, sc->size + sizeof(sc->size));
}

shmchunk* shm_read(jet_int shmfd)
{
    jet_int *p = (jet_int*)shmat(shmfd, NULL, 0);
    jet_int *kp = p;
    if (shm_data_exist(p) == JET_ERROR) {
        return NULL;
    }

    shm_to_begin(&p);

    shmchunk *sc = malloc(sizeof(sc));
    sc->size = *p++;
    sc->data = malloc(sc->size);
    memcpy(sc->data, p, sc->size);
    shm_begin_move(kp, sc->size + sizeof(sc->size));

    return sc;
}


/**************************************************************test***********************************************/
void shm_show_info(jet_int shmfd)
{
    jet_int *p = (jet_int*)shmat(shmfd, NULL, 0);
    jet_int msize = *p++;
    jet_int begin = *p++;
    jet_int end = *p;

    printf("----------------shm size:%d begin:%d end:%d\n", msize, begin, end);
}

void shm_pre_test()
{
    jet_int shmfd = shm_create(SHM_LOG_KEY, SHM_LOG_SIZE);
    printf("shmfd:%d\n", shmfd);
    shm_show_info(shmfd);

    shmchunk sc;
    char *c = "hello world!";
    sc.data = malloc(sc.size);
    sc.size = strlen(c) + 1;
    memcpy(sc.data, c, sc.size);
    shm_write(shmfd, &sc);
    shmchunk *rsc = shm_read(shmfd);
    printf("read rsc size:%d data:%s\n", rsc->size, (char*)rsc->data);
    free(sc.data);

    shm_show_info(shmfd);

    shmchunk sc1;
    char *c1 = "hello Jet!";
    sc1.data = malloc(sc1.size);
    sc1.size = strlen(c1) + 1;
    memcpy(sc1.data, c1, sc1.size);
    shm_write(shmfd, &sc1);
    shmchunk *rsc1 = shm_read(shmfd);
    printf("read rsc1 size:%d data:%s\n", rsc1->size, (char*)rsc1->data);
    free(sc1.data);

    shmchunk sc2;
    char *c2 = "hello C!";
    sc2.data = malloc(sc2.size);
    sc2.size = strlen(c2) + 1;
    memcpy(sc2.data, c2, sc2.size);
    shm_write(shmfd, &sc2);
    shmchunk *rsc2 = shm_read(shmfd);
    printf("read rsc2 size:%d data:%s\n", rsc2->size, (char*)rsc2->data);
    free(sc2.data);

    shm_show_info(shmfd);
    shm_del(SHM_LOG_KEY);

    free(rsc->data);
    free(rsc1->data);
    free(rsc2->data);
    free(rsc);
    free(rsc1);
    free(rsc2);
}