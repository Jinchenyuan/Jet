#include "worker.h"
#include "../core/jet_shm.h"

/*******************************************test***************************************/
void worker_test_proc_write(void *data)
{
    jet_int shmfd = (jet_int)data;
    printf("write process shmfd %d.\n", shmfd);
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

void worker_test_proc_cycle(void *data)
{   
    jet_int loop_times = 0;
    while (loop_times < 10)
    {
        loop_times++;
        printf("cycle times %d.\n", loop_times);
        sleep(1);
    }
    printf("cycle over.\n");
    exit(0);
}