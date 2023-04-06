#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "mpsoc_mmap.h"

static int fd_dev_mem = -1;

void mpsoc_memset(void *_buf, int val, size_t size)
{
    uint8_t *buf = (uint8_t *)_buf;
    for (size_t i = 0; i < size; i++) {
        buf[i] = val;
    }
}

void *mpsoc_mmap_shared (int *_fd)
{
    int fd;
    void *buf = NULL;
    size_t buf_size = 0x04000000;

    if ((fd  = open("/dev/udmabuf0", O_RDWR | O_SYNC)) != -1) {
        buf = mmap(NULL, buf_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    }
    *_fd = fd;
    return buf;
}

void *mpsoc_mmap (uint64_t paddr, uint64_t psize)
{
    void *vptr;
    if (fd_dev_mem == -1) {
        fd_dev_mem = open("/dev/mem", O_RDWR | O_SYNC);
    }
    if (fd_dev_mem != -1) {
        vptr = (uint64_t *)mmap(NULL, psize, PROT_READ|PROT_WRITE, MAP_SHARED, fd_dev_mem, paddr);
    }
    return vptr;
}

void mpsoc_unmap_shared (int fd)
{
    close(fd);
    close(fd_dev_mem);
}