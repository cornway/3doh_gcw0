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

#define BIT_2_MASK(_x) ((1 << (_x)) - 1)
#define TRIM_U32(_x) (_x) > 32 ? 32 : (_x) < 1 ? 1 : (_x)

static uint32_t cached_data = 0;
static uint32_t cached_data_valid = 0;
static uint32_t cached_bits = 0;

static uint32_t _reverse_u32 (uint32_t x, uint32_t bits)
{
	uint32_t reverse = 0;
	uint8_t bit = 0;
	int i;
	for (i = 0; i < bits; i++) {
	    bit = x & (1 << i) ? 1 : 0;
		reverse |= bit << (bits - 1 - i);
	}
	return reverse;
}

static uint32_t read_cached(struct BitReaderBig *bit)
{
	if (!cached_data_valid) {
		uint32_t address = (bit->buf + bit->point) & (~0x3);
		cached_data = _reverse_u32(_mem_read32(address), 32);
		cached_data_valid = 1;
	}
	return cached_data;
}

void BitReaderBig_AttachBuffer(struct BitReaderBig *bit, uint32_t buff)
{
	bit->buf      = buff;
	bit->point    = 0;
	bit->bitpoint = 0;
	cached_data_valid = false;
	cached_bits  = 0;
	read_cached(bit);
}

void BitReaderBig_Skip(struct BitReaderBig *bit, uint32_t bits)
{
	cached_bits += bits;
	if (cached_bits >= 0x1f) {
		cached_bits &= 0x1f;
		cached_data_valid = 0;
	}
	bits         += bit->bitpoint;
	bit->point   += (bits >> 3);
	bit->bitpoint = bits & 7;
}

uint32_t BitReaderBig_Read(struct BitReaderBig *bit, uint8_t bitrate)
{
	int32_t bitcnt;
	uint32_t retval = 0;
	uint32_t tmp;
	uint32_t shift;
	uint32_t bits = 0;

	bitrate  = TRIM_U32(bitrate);
	bitcnt = bitrate;
	if (!bit->buf)
		return retval;

	bits = bit->bitpoint + (bit->point & 0x3) * 8;
	assert(bits < 32);

	retval = read_cached(bit);
	retval >>= bits;
	BitReaderBig_Skip(bit, bitrate);

	if (!cached_data_valid) {
		tmp = read_cached(bit);
		shift = 32 - bits;
		retval |= tmp << shift;
	}
	return _reverse_u32(retval, bitrate);
}
