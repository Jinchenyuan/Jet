#ifndef __JET_SEM_H_
#define __JET_SEM_H_

#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "jet_define.h"

#define SEM_FLG_CHECK       0640

#define SEM_LOG_KEY         0x70001
#define SEM_TCP_KEY         0x70002
#define SEM_UDP_KEY         0x70003
#define SEM_HTTP_KEY        0x70004

/******************************************test************************************/
void sem_pre_test();

#endif