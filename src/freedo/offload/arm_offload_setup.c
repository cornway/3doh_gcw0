
#include <stdint.h>

#include <mpsoc_infra.h>
#include <arm.h>

static int shared_pRam_map_fd = -1;
static mpsoc_dev_t mpsoc_dev;

void *_arm_offload_setup (void)
{

	void *dram1 = mpsoc_mmap_shared(&shared_pRam_map_fd, DRAM1_SIZE);

	mpsoc_dev.dev = mpsoc_dev_open("axi_bram_ctrl_ram");
	mpsoc_assert(mpsoc_dev.dev != NULL);

	mpsoc_dev.io = mpsoc_dev_io(mpsoc_dev.dev, dram1 + DRAM1_SIZE);
    void *ioptr = mpsoc_dev.io;
	mpsoc_assert(ioptr != NULL);

    return dram1;
}

void _arm_offload_destroy (void)
{
    mpsoc_dev_close(&mpsoc_dev);
	mpsoc_unmap_shared(shared_pRam_map_fd);
}

void *_arm_offload_mremap(void *pRamOld, size_t pRamSizeOld, void *pRam, size_t pRamSize)
{
    void *ptr =  mpsoc_mrmap(pRamOld, pRamSizeOld, pRam, pRamSize);
}