#include "worker.h"
#include "../core/jet_shm.h"






/*******************************************test***************************************/
void worker_test_proc_write(void *data)
{
    char *p = (char *)data;
    jet_int pid = getpid();
    printf("worker write process pid:%d data:%s\n", pid, p);

    jet_int shmfd = shm_get(SHM_LOG_KEY);
    if (shmfd == JET_ERROR) {
        fprintf(stderr, "get shmfd failed.\n");
        exit(1);
    }

    for (;;) {
        shmchunk sc;
        char *c = "hello world!";
        sc.data = malloc(sc.size);
        sc.size = strlen(c) + 1;
        memcpy(sc.data, c, sc.size);
        shm_write(shmfd, &sc);
        printf("write over.\n");
        sleep(1);
    }  

    exit(0);
}

void worker_test_proc_read(void *data)
{
    char *p = (char *)data;
    jet_int pid = getpid();
    printf("worker read process pid:%d data:%s\n", pid, p);

    jet_int shmfd = shm_get(SHM_LOG_KEY);
    if (shmfd == JET_ERROR) {
        fprintf(stderr, "get shmfd failed.\n");
        exit(1);
    }

    for (;;) {
        shmchunk *rsc = shm_read(shmfd);
        if (rsc) {
            printf("read rsc size:%d data:%s\n", rsc->size, (char*)rsc->data);
            free(rsc->data);
            free(rsc);
        }
        else {
            sleep(1);
        }
    }

    exit(0);
}