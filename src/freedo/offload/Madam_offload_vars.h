#ifndef MADAM_OFFLOAD_VARS_H
#define MADAM_OFFLOAD_VARS_H

#include <stdint.h>

typedef struct MADAMDatum {
	uint32_t *mregs;
	uint32_t *PLUT;
	uint8_t *PBUSQueue;
	int32_t *RMOD;
	int32_t *WMOD;
	unsigned int *_madam_FSM;
	uint32_t *utils;
} MADAMDatum_t;

extern int32_t *madam_offload_vars_signed_ptr;
extern uint32_t *madam_offload_vars_unsigned_ptr;

#if 1

#define HDDX1616    (madam_offload_vars_signed_ptr[0])
#define HDDY1616    (madam_offload_vars_signed_ptr[1])
#define HDX1616     (madam_offload_vars_signed_ptr[2])
#define HDY1616     (madam_offload_vars_signed_ptr[3])
#define VDX1616     (madam_offload_vars_signed_ptr[4])
#define VDY1616     (madam_offload_vars_signed_ptr[5])
#define XPOS1616    (madam_offload_vars_signed_ptr[6])
#define YPOS1616    (madam_offload_vars_signed_ptr[7])
#define HDX1616_2   (madam_offload_vars_signed_ptr[8])
#define HDY1616_2   (madam_offload_vars_signed_ptr[9])
#define TEXTURE_WI_START (madam_offload_vars_signed_ptr[10])
#define TEXTURE_HI_START (madam_offload_vars_signed_ptr[11])
#define TEXEL_INCX  (madam_offload_vars_signed_ptr[12])
#define TEXEL_INCY  (madam_offload_vars_signed_ptr[13])
#define TEXTURE_WI_LIM (madam_offload_vars_signed_ptr[14])
#define TEXTURE_HI_LIM (madam_offload_vars_signed_ptr[15])

#define TEXEL_FUN_NUMBER    (madam_offload_vars_signed_ptr[16])

#define SPRWI           (madam_offload_vars_signed_ptr[17])
#define SPRHI           (madam_offload_vars_signed_ptr[18])
#define CELCYCLES       (madam_offload_vars_signed_ptr[19])
#define __smallcycles   (madam_offload_vars_signed_ptr[20])
//static SDL_Event cpuevent;
#define BITCALC         (madam_offload_vars_signed_ptr[21])



#define BITADDR         (madam_offload_vars_unsigned_ptr[0])
#define BITBUFLEN       (madam_offload_vars_unsigned_ptr[1])
#define BITBUF          (madam_offload_vars_unsigned_ptr[2])

#define CCBFLAGS        (madam_offload_vars_unsigned_ptr[3])
#define PIXC            (madam_offload_vars_unsigned_ptr[4])
#define PRE0            (madam_offload_vars_unsigned_ptr[5])
#define PRE1            (madam_offload_vars_unsigned_ptr[6])
#define TARGETPROJ      (madam_offload_vars_unsigned_ptr[7])
#define SRCDATA         (madam_offload_vars_unsigned_ptr[8])
#define PLUTF           (madam_offload_vars_unsigned_ptr[9])
#define PDATF           (madam_offload_vars_unsigned_ptr[10])
#define NCCBF           (madam_offload_vars_unsigned_ptr[11])
#define PXOR1           (madam_offload_vars_unsigned_ptr[12])
#define PXOR2           (madam_offload_vars_unsigned_ptr[13])

#else

unsigned int BITADDR;
unsigned int BITBUFLEN;
unsigned int BITBUF;
unsigned int CCBFLAGS, /*PLUTDATA*/ PIXC, PRE0, PRE1, TARGETPROJ, SRCDATA, debug;
int SPRWI, SPRHI;
unsigned int PLUTF, PDATF, NCCBF;
int CELCYCLES, __smallcycles;
bool ADD;
//static SDL_Event cpuevent;
int BITCALC;

static int HDDX1616, HDDY1616, HDX1616, HDY1616, VDX1616, VDY1616, XPOS1616, YPOS1616, HDX1616_2, HDY1616_2;
static unsigned int CEL_ORIGIN_VH_VALUE;
static int8_t TEXEL_FUN_NUMBER;
static int TEXTURE_WI_START, TEXTURE_HI_START, TEXEL_INCX, TEXEL_INCY;
static int TEXTURE_WI_LIM, TEXTURE_HI_LIM;
uint32_t PXOR1, PXOR2;

#endif

/* === CCB control word flags === */
#define CCB_SKIP        0x80000000
#define CCB_LAST        0x40000000
#define CCB_NPABS       0x20000000
#define CCB_SPABS       0x10000000
#define CCB_PPABS       0x08000000
#define CCB_LDSIZE      0x04000000
#define CCB_LDPRS       0x02000000
#define CCB_LDPPMP      0x01000000
#define CCB_LDPLUT      0x00800000
#define CCB_CCBPRE      0x00400000
#define CCB_YOXY        0x00200000
#define CCB_ACSC        0x00100000
#define CCB_ALSC        0x00080000
#define CCB_ACW         0x00040000
#define CCB_ACCW        0x00020000
#define CCB_TWD         0x00010000
#define CCB_LCE         0x00008000
#define CCB_ACE         0x00004000
#define CCB_reserved13  0x00002000
#define CCB_MARIA       0x00001000
#define CCB_PXOR        0x00000800
#define CCB_USEAV       0x00000400
#define CCB_PACKED      0x00000200
#define CCB_POVER_MASK  0x00000180
#define CCB_PLUTPOS     0x00000040
#define CCB_BGND        0x00000020
#define CCB_NOBLK       0x00000010
#define CCB_PLUTA_MASK  0x0000000F

#define CCB_POVER_SHIFT  7
#define CCB_PLUTA_SHIFT  0

#define PMODE_PDC   ((0x00000000) << CCB_POVER_SHIFT) /* Normal */
#define PMODE_ZERO  ((0x00000002) << CCB_POVER_SHIFT)
#define PMODE_ONE   ((0x00000003) << CCB_POVER_SHIFT)

//  === CCBCTL0 flags ===
#define B15POS_MASK   0xC0000000
#define B0POS_MASK    0x30000000
#define SWAPHV        0x08000000
#define ASCALL        0x04000000
#define _CCBCTL0_u25  0x02000000
#define CFBDSUB       0x01000000
#define CFBDLSB_MASK  0x00C00000
#define PDCLSB_MASK   0x00300000

#define B15POS_SHIFT  30
#define B0POS_SHIFT   28
#define CFBD_SHIFT    22
#define PDCLSB_SHIFT  20

//  B15POS_MASK definitions
#define B15POS_0    0x00000000
#define B15POS_1    0x40000000
#define B15POS_PDC  0xC0000000

//  B0POS_MASK definitions
#define B0POS_0     0x00000000
#define B0POS_1     0x10000000
#define B0POS_PPMP  0x20000000
#define B0POS_PDC   0x30000000

/*
   //  CFBDLSB_MASK definitions
 #define CFBDLSB_0      0x00000000
 #define CFBDLSB_CFBD0  0x00400000
 #define CFBDLSB_CFBD4  0x00800000
 #define CFBDLSB_CFBD5  0x00C00000

   //  PDCLSB_MASK definitions
 #define PDCLSB_0     0x00000000
 #define PDCLSB_PDC0  0x00100000
 #define PDCLSB_PDC4  0x00200000
 #define PDCLSB_PDC5  0x00300000
 */

/* === Cel first preamble word flags === */
#define PRE0_LITERAL    0x80000000
#define PRE0_BGND       0x40000000
#define PREO_reservedA  0x30000000
#define PRE0_SKIPX_MASK 0x0F000000
#define PREO_reservedB  0x00FF0000
#define PRE0_VCNT_MASK  0x0000FFC0
#define PREO_reservedC  0x00000020
#define PRE0_LINEAR     0x00000010
#define PRE0_REP8       0x00000008
#define PRE0_BPP_MASK   0x00000007

#define PRE0_SKIPX_SHIFT 24
#define PRE0_VCNT_SHIFT  6
#define PRE0_BPP_SHIFT   0

/* PRE0_BPP_MASK definitions */
#define PRE0_BPP_1   0x00000001
#define PRE0_BPP_2   0x00000002
#define PRE0_BPP_4   0x00000003
#define PRE0_BPP_6   0x00000004
#define PRE0_BPP_8   0x00000005
#define PRE0_BPP_16  0x00000006

/* Subtract this value from the actual vertical source line count */
#define PRE0_VCNT_PREFETCH    1


/* === Cel second preamble word flags === */
#define PRE1_WOFFSET8_MASK   0xFF000000
#define PRE1_WOFFSET10_MASK  0x03FF0000
#define PRE1_NOSWAP          0x00004000
#define PRE1_TLLSB_MASK      0x00003000
#define PRE1_LRFORM          0x00000800
#define PRE1_TLHPCNT_MASK    0x000007FF

#define PRE1_WOFFSET8_SHIFT   24
#define PRE1_WOFFSET10_SHIFT  16
#define PRE1_TLLSB_SHIFT      12
#define PRE1_TLHPCNT_SHIFT    0

#define PRE1_TLLSB_0     0x00000000
#define PRE1_TLLSB_PDC0  0x00001000 /* Normal */
#define PRE1_TLLSB_PDC4  0x00002000
#define PRE1_TLLSB_PDC5  0x00003000

/* Subtract this value from the actual word offset */
#define PRE1_WOFFSET_PREFETCH 2
/* Subtract this value from the actual pixel count */
#define PRE1_TLHPCNT_PREFETCH 1

#define PPMP_0_SHIFT 0
#define PPMP_1_SHIFT 16

#define PPMPC_1S_MASK  0x00008000
#define PPMPC_MS_MASK  0x00006000
#define PPMPC_MF_MASK  0x00001C00
#define PPMPC_SF_MASK  0x00000300
#define PPMPC_2S_MASK  0x000000C0
#define PPMPC_AV_MASK  0x0000003E
#define PPMPC_2D_MASK  0x00000001

#define PPMPC_MS_SHIFT  13
#define PPMPC_MF_SHIFT  10
#define PPMPC_SF_SHIFT  8
#define PPMPC_2S_SHIFT  6
#define PPMPC_AV_SHIFT  1

/* PPMPC_1S_MASK definitions */
#define PPMPC_1S_PDC   0x00000000
#define PPMPC_1S_CFBD  0x00008000

/* PPMPC_MS_MASK definitions */
#define PPMPC_MS_CCB         0x00000000
#define PPMPC_MS_PIN         0x00002000
#define PPMPC_MS_PDC_MFONLY  0x00004000
#define PPMPC_MS_PDC         0x00004000

/* PPMPC_MF_MASK definitions */
#define PPMPC_MF_1  0x00000000
#define PPMPC_MF_2  0x00000400
#define PPMPC_MF_3  0x00000800
#define PPMPC_MF_4  0x00000C00
#define PPMPC_MF_5  0x00001000
#define PPMPC_MF_6  0x00001400
#define PPMPC_MF_7  0x00001800
#define PPMPC_MF_8  0x00001C00

/* PPMPC_SF_MASK definitions */
#define PPMPC_SF_2   0x00000100
#define PPMPC_SF_4   0x00000200
#define PPMPC_SF_8   0x00000300
#define PPMPC_SF_16  0x00000000

/* PPMPC_2S_MASK definitions */
#define PPMPC_2S_0     0x00000000
#define PPMPC_2S_CCB   0x00000040
#define PPMPC_2S_CFBD  0x00000080
#define PPMPC_2S_PDC   0x000000C0

/* PPMPC_2D_MASK definitions */
#define PPMPC_2D_1  0x00000000
#define PPMPC_2D_2  0x00000001

//CelEngine STATBits
#define STATBITS        mregs[0x28]

#define SPRON           0x10
#define SPRPAU          0x20

//CelEngine Registers
#define SPRSTRT         0x100
#define SPRSTOP         0x104
#define SPRCNTU         0x108
#define SPRPAUS         0x10c

#define CCBCTL0         mregs[0x110]
#define REGCTL0         mregs[0x130]
#define REGCTL1         mregs[0x134]
#define REGCTL2         mregs[0x138]
#define REGCTL3         mregs[0x13c]

#define CLIPXVAL        ((int)mregs[0x134] & 0x3ff)
#define CLIPYVAL        ((int)(mregs[0x134] >> 16) & 0x3ff)

#define PIXSOURCE       (mregs[0x138])
#define FBTARGET        (mregs[0x13c])

#define CURRENTCCB      mregs[0x5a0]
//next ccb == 0 stop the engine
#define NEXTCCB         mregs[0x5a4]
#define PLUTDATA        mregs[0x5a8]
#define PDATA           mregs[0x5ac]
#define ENGAFETCH       mregs[0x5b0]
#define ENGALEN         mregs[0x5b4]
#define ENGBFETCH       mregs[0x5b8]
#define ENGBLEN         mregs[0x5bc]
#define PAL_EXP         (&mregs[0x5d0])

//*******************************************

#define PDV(x) ((((x) - 1) & 3) + 1)


#define MIN(x, y) (x) + (((signed int)((y) - (x)) >> 31 & ((y) - (x))))
#define MAX(x, y) (y) - (((signed int)((y) - (x)) >> 31 & ((y) - (x))))

#define TESTCLIP(cx, cy) ( ((cx) >= 0) && ((cx) <= CLIPXVAL) && ((cy) >= 0) && ((cy) <= CLIPYVAL) )


#define  XY2OFF(a, b, c)   (  (((b) >> 1) * (c) /*bitmap width*/)   + (((int)(b) & 1) << 1) +    (a)    )


#define PBMASK 0x80000000
#define KUP    0x08000000
#define KDN    0x10000000
#define KRI    0x04000000
#define KLE    0x02000000
#define KA     0x01000000
#define KB     0x00800000
#define KC     0x00400000
#define KP     0x00200000
#define KX     0x00100000
#define KRS    0x00080000
#define KLS    0x00040000
#define FIXP16_SHIFT     16
#define FIXP16_MAG       65536
#define FIXP16_DP_MASK   0x0000ffff
#define FIXP16_WP_MASK   0xffff0000
#define FIXP16_ROUND_UP  0x0000ffff //0x8000

#ifndef DONTPACK
#pragma pack(push,1)
#endif

struct cp1btag {
	uint16_t c : 1;
	uint16_t pad : 15;
};
struct cp2btag {
	uint16_t c : 2;
	uint16_t pad : 14;
};
typedef struct cp4btag {
	uint16_t c : 4;
	uint16_t pad : 12;
} cp4b;
struct cp6btag {
	uint16_t c : 5;
	uint16_t pw : 1;
	uint16_t pad : 10;
};
struct cp8btag {
	uint16_t c : 5;
	uint16_t mpw : 1;
	uint16_t m : 2;
	uint16_t pad : 8;
};
struct cp16btag {
	uint16_t c : 5;
	uint16_t mb : 3;
	uint16_t mg : 3;
	uint16_t mr : 3;
	uint16_t pad : 1;
	uint16_t pw : 1;
};
struct up8btag {
	uint16_t b : 2;
	uint16_t g : 3;
	uint16_t r : 3;
	uint16_t pad : 8;
};
struct up16btag {
	uint16_t bw : 1;
	uint16_t b : 4;
	uint16_t g : 5;
	uint16_t r : 5;
	uint16_t p : 1;
};
struct res16btag {
	uint16_t b : 5;
	uint16_t g : 5;
	uint16_t r : 5;
	uint16_t p : 1;
};

union pdeco {
	unsigned int raw;
	struct cp1btag c1b;
	struct cp2btag c2b;
	struct cp4btag c4b;
	struct cp6btag c6b;
	struct cp8btag c8b;
	struct cp16btag c16b;
	struct up8btag u8b;
	struct up16btag u16b;
	struct res16btag r16b;
};

#ifndef DONTPACK
#pragma pack(pop)
#endif

// TYPES ///////////////////////////////////////////////////////////////////


// CLASSES /////////////////////////////////////////////////////////////////
uint32_t  mread(uint32_t addr);
void  mwrite(uint32_t addr, uint32_t val);
int TestInitVisual(int packed);
int Init_Line_Map(void);
void Init_Scale_Map(void);
void Init_Arbitrary_Map(void);
void TexelDraw_BitmapRow(uint16_t LAMV, int xcur, int ycur, int cnt);
void TexelDraw_Line(uint16_t CURPIX, uint16_t LAMV, int xcur, int ycur, int cnt);
int  TexelDraw_Scale(uint16_t CURPIX, uint16_t LAMV, int xcur, int ycur, int deltax, int deltay);
int  TexelDraw_Arbitrary(uint16_t CURPIX, uint16_t LAMV, int xA, int yA, int xB, int yB, int xC, int yC, int xD, int yD);
void  DrawPackedCel_New(void);
void  DrawLiteralCel_New(void);
void  DrawLRCel_New(void);
void HandleDMA8(void);
void DMAPBus(void);

// general 3D vertex class

#define INT1220(a)       ((signed int)(a) >> 20)
#define INT1220up(a) ((signed int)((a) + (1 << 19)) >> 20)

static struct {
	uint32_t plutaCCBbits;
	uint32_t pixelBitsMask;
	bool tmask;
} pdec;

static struct {
	uint32_t pmode;
	uint32_t pmodeORmask;
	uint32_t pmodeANDmask;
	bool Transparent;
} pproj;


#endif /*MADAM_OFFLOAD_VARS_H*/