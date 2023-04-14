/*
   www.freedo.org
   The first and only working 3DO multiplayer emulator.

   The FreeDO licensed under modified GNU LGPL, with following notes:

 *   The owners and original authors of the FreeDO have full right to develop closed source derivative work.
 *   Any non-commercial uses of the FreeDO sources or any knowledge obtained by studying or reverse engineering
        of the sources, or any other material published by FreeDO have to be accompanied with full credits.
 *   Any commercial uses of FreeDO sources or any knowledge obtained by studying or reverse engineering of the sources,
        or any other material published by FreeDO is strictly forbidden without owners approval.

   The above notes are taking precedence over GNU LGPL in conflicting situations.

   Project authors:

   Alexander Troosh
   Maxim Grishin
   Allen Wright
   John Sammons
   Felix Lazarev
 */
#include <assert.h>
#include <byteswap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitop.h"
#include "arm.h"

#include "Madam_offload_vars.h"

#define BITOP_OFFLOAD_ATTACH_OP 0x0
#define BITOP_OFFLOAD_SKIP_OP 0x1
#define BITOP_OFFLOAD_READ_OP 0x2

extern struct MADAMDatum madam;

static void BitReaderBig_WaitReady (void)
{
	while (madam.utils[2]) {;}
}

void BitReaderBig_AttachBuffer(struct BitReaderBig *bit, uint32_t buff)
{
	madam.utils[0] = 0x70000000;
	madam.utils[1] = buff;
	BitReaderBig_WaitReady();
	bit->point = 0;
}

void BitReaderBig_Skip(struct BitReaderBig *bit, uint32_t bits)
{
	madam.utils[2] = BITOP_OFFLOAD_SKIP_OP | (bits << 16) | (bits << 8);
	BitReaderBig_WaitReady();
	bit->point = madam.utils[4];
}

uint32_t BitReaderBig_Read(struct BitReaderBig *bit, uint8_t bitrate)
{
	madam.utils[2] = BITOP_OFFLOAD_READ_OP | (bitrate << 8) | (bitrate << 16);
	BitReaderBig_WaitReady();
	bit->point = madam.utils[4];
	return madam.utils[3];
}