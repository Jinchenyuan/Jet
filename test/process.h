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
    jet_int pid = jet_fork(worker_test_proc_read, "test read.");
    if (pid != 0) {
        jet_int ppid = getpid();
        printf("create woker process pid:%d main pid:%d\n", pid, ppid);
    }
    //write woker
    pid = jet_fork(worker_test_proc_write, "test write.");
    if (pid != 0) {
        jet_int ppid = getpid();
        printf("create woker process pid:%d main pid:%d\n", pid, ppid);
    }
    jet_int status;
    for (;;) {
        pid = waitpid(-1, &status, WNOHANG);
        if (pid == 0) {
            return;
        }
    }
}

#endif