#include "jet_define.h"
#include "jet_thread.h"
#include "jet_shm.h"
#include "jet_sem.h"
#include "jet_process.h"
#include "../worker/worker.h"

#include "../3rd/ini/iniparser.h"

#include "../test/shm.h"
#include "../test/thread.h"
#include "../test/process.h"
#include "../test/sem.h"

int read_conf(const char *p, dictionary *d)
{
    d = iniparser_load(p);
    if (!d)
    {
        fprintf(stderr, "Need config file, See README.");
        return -1;
    }
    iniparser_dump(d, stderr);
    return 0;
}

int main(int argc, char *argv[])
{
    dictionary *d = NULL;
    read_conf("config/config.cfg", d);

    // thread_test();
    // shm_pre_test();
    // sem_pre_test();
    process_pre_test();
    return 0;
}