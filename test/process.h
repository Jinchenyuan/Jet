#ifndef _TEST_PROCESS_H_
#define _TEST_PROCESS_H_

#include "../core/jet_define.h"
#include "../core/jet_process.h"
#include "../worker/worker.h"
#include <sys/wait.h>

/*******************************************************test***************************************/
void process_pre_test()
{
    //read worker
    shm_create(SHM_LOG_KEY, SHM_LOG_SIZE);
    jet_int shmfd = shm_get(SHM_LOG_KEY);
    if (shmfd == JET_ERROR) {
        fprintf(stderr, "process_pre_test get shmfd failed.\n");
        exit(1);
    }
    else
    {
        printf("process_pre_test create shmfd:%d.\n", shmfd);
    }

    //write worker
    jet_int pid = jet_fork(worker_test_proc_write, shmfd);
    if (pid != 0) {
        jet_int ppid = getpid();
        printf("create woker write process pid:%d main pid:%d\n", pid, ppid);
    }

    //cycle worker
    pid = jet_fork(worker_test_proc_cycle, "cycle");
    if (pid != 0) {
        jet_int ppid = getpid();
        printf("create woker cycle process pid:%d main pid:%d\n", pid, ppid);
    }

    //reader
    for (;;) {
        shmchunk *rsc = shm_read(shmfd);
        if (rsc) {
            printf("read rsc size:%d data:%s\n", rsc->size, (char*)rsc->data);
            free(rsc->data);
            free(rsc);
        }
        sleep(1);
        // else {
        //     sleep(1);
        // }
    }

    jet_int status;
    for (;;) {
        pid = waitpid(-1, &status, WNOHANG);
        if (pid == 0) {
            printf("worker process over!");
            goto TEST_OVER;
        }
    }

TEST_OVER:
    shm_del(SHM_LOG_KEY);
}

#endif