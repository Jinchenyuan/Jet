#ifndef __JET_SHM_H_
#define __JET_SHM_H_

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "jet_define.h"


#define SHM_FLG_PERMS       0660

#define SHM_LOG_KEY         0x70001
#define SHM_TCP_KEY         0x70002
#define SHM_UDP_KEY         0x70003
#define SHM_HTTP_KEY        0x70004

#define SHM_LOG_SIZE        1024 * 1024     /*1M memory*/
#define SHM_TCP_SIZE        4096 * 10       /*40 Kb usual pagesize == 4094Kb*/
#define SHM_UDP_SIZE        4096 * 10       /*40 Kb usual pagesize == 4094Kb*/
#define SHM_HTTP_SIZE       4096 * 10       /*40 Kb usual pagesize == 4094Kb*/

#define SHM_DEFAULT_SIZE    4096

#define GET_SIZE_BY_KEY(KEY)    \
    ({jet_int ret;  \
    switch (KEY)    \
    {   \
    case SHM_LOG_KEY:   \
        ret = SHM_LOG_SIZE; \
        break;  \
    case SHM_TCP_KEY:   \
        ret = SHM_TCP_SIZE; \
        break;  \
    case SHM_UDP_KEY:   \
        ret = SHM_UDP_SIZE; \
        break;  \
    case SHM_HTTP_KEY:  \
        ret = SHM_HTTP_SIZE;    \
        break;  \
    default:    \
        ret = SHM_DEFAULT_SIZE; \
        break;  \
    }   \
    ret;})

/**
 * get shared memory fd bey shm key
 * if not found return JET_ERROR
*/
jet_int shm_get(jet_int key);

/**
 * delete shared memory by shm key
*/
void shm_del(jet_int key);

/**
 * create shared memory by key.
 * if existing, will delete it before create
 * size: set shared memory size.
*/
jet_int shm_create(jet_int key, jet_uint size);

/**
 * write shmchunk to shared memory
 * if shared memory overflow, process will exit.
*/
void shm_write(jet_int shmfd, shmchunk *sc);

/**
 * read contents from shared memory.
 * 
 * return NULL when did not wrote.
*/
shmchunk* shm_read(jet_int shmfd);


/*****************************test*************************************/
void shm_pre_test();


#endif /*__JET_SHM_H_*/