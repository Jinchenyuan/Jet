#ifndef __JET_SHM_H_
#define __JET_SHM_H_

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "jet_define.h"


#define SHM_FLG_CHECK       0640

#define SHM_LOG_KEY         0x70001
#define SHM_TCP_KEY         0x70002
#define SHM_UDP_KEY         0x70003
#define SHM_HTTP_KEY        0x70004

#define SHM_LOG_SIZE        1024
#define SHM_TCP_SIZE        612
#define SHM_UDP_SIZE        612
#define SHM_HTTP_SIZE       612

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


void shm_pre_test();


#endif /*__JET_SHM_H_*/