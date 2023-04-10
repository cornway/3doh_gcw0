#ifndef MPSOC_INFRA_H
#define MPSOC_INFRA_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "mpsoc_mmap.h"

typedef struct {
    void *dev;
    void *io;
} mpsoc_dev_t;

int mpsoc_infra_init (void);
int mpsoc_infra_close (void);
void *mpsoc_dev_open(const char *dev_name);
void mpsoc_dev_close(void *dev);
void *mpsoc_dev_io(const void *_dev);

void mpsoc_log (const char * format, ...);

void mpsoc_abort (void);

#define mpsoc_assert(x) do { \
    if (!(x)) {mpsoc_abort();} \
} while (0)

#endif /*MPSOC_INFRA_H*/
