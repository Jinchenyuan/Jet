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