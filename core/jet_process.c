#include "jet_process.h"
#include "../worker/worker.h"

jet_int jet_fork(jet_process proc, void *data)
{
    jet_int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "process fork failure. errno:%d\n", errno);
        exit(1);
    }

    if (pid == 0) {
        proc(data);
    }

    return pid;
}

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