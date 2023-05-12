
FPGA_OFFLOAD ?= 0
NO_VIDEO ?= 0
DEBUG ?= 1
SCALING ?= 0
CXX = g++
TARGET = 3doh
CFLAGS = -O0 -DHLE_SWI -DDONTPACK
CFLAGS += -Isrc -Isrc/freedo
LDFLAGS= -lSDL -lm

OBJS = \
	src/freedo/DiagPort.o\
	src/freedo/quarz.o\
	src/freedo/Clio.o \
	src/freedo/frame.o \
	src/freedo/vdlp.o \
	src/freedo/_3do_sys.o \
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
	src/main.o

ifeq ($(SCALING),1)
CFLAGS += -DSCALING
endif

ifeq ($(DEBUG),1)
CFLAGS += -g
endif

ifeq ($(NO_VIDEO),1)
CFLAGS += -DNO_VIDEO
endif

ifeq ($(FPGA_OFFLOAD),1)
CFLAGS += -DMPSOC
OBJS += src/freedo/offload/Madam_offload.o \
		src/freedo/offload/Madam_offload_setup.o \
		src/freedo/offload/arm_offload.o \
		src/freedo/offload/bitop_offload.o \
		src/mpsoc_infra.o \
		src/mpsoc_mmap.o
LDFLAGS += -lmetal
else
OBJS += src/freedo/Madam.o \
		src/freedo/arm.o \
		src/freedo/bitop.o \
		src/sim/simdata.o

CFLAGS += -Isrc/sim
endif

all: $(TARGET)

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJS) $(TARGET)
