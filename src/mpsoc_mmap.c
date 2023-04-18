#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#include "mpsoc_mmap.h"

static int fd_dev_mem = -1;

void mpsoc_memset(void *_buf, int val, size_t size)
{
    uint8_t *buf = (uint8_t *)_buf;
    for (size_t i = 0; i < size; i++) {
        buf[i] = val;
    }
}

void mpsoc_memset32(void *_buf, int val, size_t size)
{
    uint32_t *buf = (uint32_t *)_buf;
    for (size_t i = 0; i < size / sizeof(uint32_t); i++) {
        buf[i] = val;
    }
}

void *mpsoc_mmap_shared (int *_fd, size_t size)
{
    int fd;
    void *buf = NULL;
    size_t buf_size = size;

    if ((fd  = open("/dev/udmabuf0", O_RDWR | O_SYNC)) != -1) {
        ftruncate(fd, buf_size);
        buf = mmap(NULL, buf_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        if (MAP_FAILED == buf) {
            mpsoc_log("mpsoc_mmap failed, errno = %d\n", errno);
            buf = NULL;
        }
    }
    *_fd = fd;
    return buf;
}

void *mpsoc_mmap (uint64_t paddr, uint64_t psize, void *newAddr)
{
    void *vptr;
    uint32_t flags = MAP_SHARED;
    if (newAddr) {
        flags |= MAP_FIXED;
    }
    if (fd_dev_mem == -1) {
        fd_dev_mem = open("/dev/mem", O_RDWR | O_SYNC);
    }
    if (fd_dev_mem != -1) {
        vptr = (uint64_t *)mmap(newAddr, psize, PROT_READ|PROT_WRITE, flags, fd_dev_mem, paddr);
        if (MAP_FAILED == vptr) {
            mpsoc_log("mpsoc_mmap failed, errno = %d\n", errno);
            vptr = NULL;
        }
    }
    return vptr;
}

void mpsoc_unmap_shared (int fd)
{
    close(fd);
    close(fd_dev_mem);
}

void *mpsoc_mrmap (void *oldPtr, size_t oldSize, void *newPtr, size_t newSize)
{

    mpsoc_log("oldPtr=%p, oldSize=%x, newPre=%p, newSize=%x\n",
        oldPtr, oldSize, newPtr, newSize);

    void *ptr = mremap(oldPtr, oldSize, newSize, MREMAP_FIXED, newPtr);
    if (MAP_FAILED == ptr) {
        mpsoc_log("mpsoc_mrmap failed, errno = %d\n", errno);
        ptr = NULL;
    }
    return ptr;
}