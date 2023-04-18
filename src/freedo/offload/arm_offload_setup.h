#ifndef ARM_OFFLOAD_SETUP_H
#define ARM_OFFLOAD_SETUP_H

#include <mpsoc_infra.h>

void *_arm_offload_setup (void);
void _arm_offload_destroy(void);
void *_arm_offload_mremap(void *pRamOld, size_t pRamSizeOld, void *pRam, size_t pRamSize);

#endif /*ARM_OFFLOAD_SETUP_H*/