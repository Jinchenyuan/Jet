#ifndef _TEST_SHM_H_
#define _TEST_SHM_H_
#include "../core/jet_shm.h"

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

#endif