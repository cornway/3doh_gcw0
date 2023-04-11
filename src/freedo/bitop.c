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

#include <byteswap.h>
#include <stdint.h>
#include "bitop.h"
#include "arm.h"

#define BIT_2_MASK(_x) ((1 << (_x)) - 1)
#define TRIM_U32(_x) (_x) > 32 ? 32 : (_x) < 1 ? 1 : (_x)

static uint32_t cached_addr;
static uint32_t cached_data[1];
static uint8_t *cached_data_ptr = (uint8_t *)cached_data;

static uint8_t _mem_read8_cached (uint32_t addr)
{
	if (addr >= cached_addr + sizeof(uint32_t)) {
		cached_addr = addr & ~0x3;
		cached_data[0] = __bswap_32(_mem_read32(cached_addr));
	}
	return cached_data_ptr[addr & 0x3];
}

void BitReaderBig_AttachBuffer(struct BitReaderBig *bit, uint32_t buff)
{
	bit->buf      = buff;
	bit->point    = 0;
	bit->bitpoint = 0;
	cached_addr = 0;
}

void BitReaderBig_Skip(struct BitReaderBig *bit, uint32_t bits)
{
	bits         += bit->bitpoint;
	bit->point   += (bits >> 3);
	bit->bitpoint = bits & 7;
}

uint32_t BitReaderBig_Read(struct BitReaderBig *bit, uint8_t bitrate)
{
	int32_t bitcnt;
	uint32_t retval = 0;

	bitrate  = TRIM_U32(bitrate);
	bitcnt = bitrate;
	if (!bit->buf)
		return retval;

	if ((8 - bit->bitpoint) > bitrate) {
		retval    = _mem_read8_cached(bit->buf + bit->point);
		retval  >>= 8 - bit->bitpoint - bitrate;
		retval   &= BIT_2_MASK(bitrate);
		bit->bitpoint += bitrate;
		return retval;
	}

	if (bit->bitpoint) {
		retval = _mem_read8_cached(bit->buf + bit->point) & BIT_2_MASK(8 - bit->bitpoint);
		bit->point++;
		bitcnt -= 8 - bit->bitpoint;
	}

	while (bitcnt >= 8) {
		retval <<= 8;
		retval  |= _mem_read8_cached(bit->buf + bit->point);
		bit->point++;
		bitcnt -= 8;
	}

	if (bitcnt) {
		retval <<= bitcnt;
		retval |= _mem_read8_cached(bit->buf + bit->point) >> (8 - bitcnt);
	}

	bit->bitpoint = bitcnt;

	return retval;
}
