#ifndef _JET_PROCESS_H_
#define _JET_PROCESS_H_

#include "jet_define.h"
#include <sys/wait.h>

typedef void (*jet_process)(void *data);

/********************************************test**********************************************/

void process_pre_test();

#endif