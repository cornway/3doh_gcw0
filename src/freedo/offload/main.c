
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

void _memset(void *_buf, int val, size_t size)
{
    uint8_t *buf = (uint8_t *)_buf;
    for (size_t i = 0; i < size; i++) {
        buf[i] = val;
    }
}

int main (int argc, char *argv[])
{
    int fd;
    uint8_t *buf = NULL;
    size_t buf_size = 0x04000000;

    printf("Main+\n");

    fd  = open("/dev/udmabuf0", O_RDWR | O_SYNC);
    printf("fd=%d size=%x\n", fd, buf_size);
    if (fd != -1) {
        buf = mmap(NULL, buf_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        printf("buf address = %p\n", buf);

        _memset(buf, 0, buf_size);
        buf[3] = 0xaa;

        printf("buf=%x\n", buf[3]);
        close(fd);
    }
    printf("Done\n");
    return 0;
}