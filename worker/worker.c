#include "worker.h"
#include "../core/jet_shm.h"






/*******************************************test***************************************/
void worker_test_proc_write(void *data)
{
    jet_int shmfd = (jet_int)data;
    jet_int pid = getpid();
    printf("worker write process pid:%d data:%d\n", pid, shmfd);

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