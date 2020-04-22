#ifndef __JET_DEFINE_H_
#define __JET_DEFINE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint32_t       jet_uint;
typedef int32_t         jet_int;

typedef char            jet_char;
typedef char            jet_bit;

typedef int64_t         jet_lint;
typedef uint64_t       jet_ulint;


struct spin_lock
{
    jet_uint lock;
};


#endif /*__JET_DEFINE_H_*/