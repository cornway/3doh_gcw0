
FPGA_OFFLOAD ?= 1
CC = gcc
TARGET = 3doh
CFLAGS = -O2 -std=gnu99 -pg -DSCALING -DHLE_SWI -DDONTPACK
CFLAGS += -Isrc -Isrc/freedo
LDFLAGS= -lSDL -lm -lmetal

OBJS = \
	src/freedo/DiagPort.o\
	src/freedo/quarz.o\
	src/freedo/Clio.o \
	src/freedo/frame.o \
	src/freedo/vdlp.o \
	src/freedo/_3do_sys.o \
	src/freedo/bitop.o \
	src/freedo/DSP.o \
	src/freedo/Iso.o \
	src/freedo/SPORT.o \
	src/freedo/XBUS.o \
	src/freedo/freedo_fixedpoint_math.o \
	src/video.o \
	src/sound.o \
	src/cdrom.o \
	src/timer.o \
	src/input.o \
	src/config.o \
	src/cuefile.o \
	src/font/font_drawing.o \
	src/mpsoc_infra.o \
	src/mpsoc_mmap.o \
	src/main.o

ifeq ($(FPGA_OFFLOAD),1)
CFLAGS += -DMPSOC
OBJS += src/freedo/offload/Madam_offload.o \
		src/freedo/offload/arm_offload.o
else
OBJS += src/freedo/Madam.o \
		src/freedo/arm.o 
endif

all: $(TARGET)

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJS) $(TARGET)
