#ifndef __JET_DEFINE_H_
#define __JET_DEFINE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>


typedef uint32_t        jet_uint;
typedef int32_t         jet_int;

typedef char            jet_char;
typedef char            jet_bit;

typedef int16_t         jet_int16;
typedef uint16_t        jet_uint16;

typedef int64_t         jet_lint;
typedef uint64_t        jet_ulint;

#define JET_OK      0
#define JET_ERROR   -1

typedef struct spinlock
{
    jet_uint        lock;
} spinlock;

typedef struct shmchunk
{
    jet_int         size;
    void            *data;
} shmchunk;

#endif /*__JET_DEFINE_H_*/