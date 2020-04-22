#ifndef __JET_LOCK_H_
#define __JET_LOCK_H_
#include "jet_define.h"

static inline void spin_lock(struct spin_lock *l) {
    while (__sync_lock_test_and_set(&(l->lock), 1) ) {}
}

static inline void spin_unlock(struct spin_lock *l) {
    __sync_lock_release(&(l->lock));
}

static inline jet_int spin_trylock(struct spin_lock *l) {
    return __sync_lock_test_and_set(&(l->lock), 1) == 0;
}

#endif /*__JET_LOCK_H_*/