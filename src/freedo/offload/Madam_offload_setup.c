
#include <mpsoc_infra.h>

#include <Madam.h>
#include "Madam_offload_vars.h"

int32_t *madam_offload_vars_signed_ptr;
uint32_t *madam_offload_vars_unsigned_ptr;

void MadamOffloadVarsInit (void *ptr)
{
    madam_offload_vars_signed_ptr = (int32_t *)ptr;

    madam_offload_vars_unsigned_ptr = (uint32_t *)(ptr + 128 * sizeof(uint32_t));
}

void _madam_mpsoc_init (mpsoc_dev_t *mpsoc_dev, struct MADAMDatum *madam)
{
	mpsoc_dev->dev = mpsoc_dev_open("axi_bram_ctrl_mregs");
	mpsoc_assert(mpsoc_dev->dev != NULL);

	mpsoc_dev->io = mpsoc_dev_io(mpsoc_dev->dev, NULL);
    void *ioptr = mpsoc_dev->io;
	mpsoc_assert(ioptr != NULL);

	madam->mregs 			= ioptr;
	madam->PLUT 			= ioptr + 0x4000;
	madam->PBUSQueue 		= ioptr + 0x8000;
	madam->RMOD 			= ioptr + 0xC000;
	madam->WMOD 			= ioptr + 0xC004;
	madam->_madam_FSM 		= ioptr + 0xC008;
	madam->utils 			= ioptr + 0x10000;

	MadamOffloadVarsInit(ioptr + 0x14000);
}