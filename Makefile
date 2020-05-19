CC = clang
TARGET = 3doh
CFLAGS = -march=native -O0 -g3 -Weverything
CFLAGS += -Isrc -Isrc/freedo
LDFLAGS= -lSDL -lm

OBJS = \
	src/freedo/arm.o \
	src/freedo/DiagPort.o\
	src/freedo/quarz.o\
	src/freedo/Clio.o \
	src/freedo/frame.o \
	src/freedo/Madam.o \
	src/freedo/vdlp.o \
	src/freedo/_3do_sys.o \
	src/freedo/bitop.o \
	src/freedo/DSP.o \
	src/freedo/Iso.o \
	src/freedo/SPORT.o \
	src/freedo/XBUS.o \
	src/video.o \
	src/sound.o \
	src/cdrom.o \
	src/timer.o \
	src/input.o \
	src/config.o \
	src/main.o

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
