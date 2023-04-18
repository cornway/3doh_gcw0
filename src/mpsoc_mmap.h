
#ifndef MPSOC_MMAP_H
#define MPSOC_MMAP_H

void mpsoc_memset(void *_buf, int val, size_t size);
void mpsoc_memset32(void *_buf, int val, size_t size);

void *mpsoc_mmap_shared (int *_fd, size_t size);
void mpsoc_unmap_shared (int fd);

void *mpsoc_mmap (uint64_t paddr, uint64_t psize, void *newAddr);
void *mpsoc_mrmap (void *oldPtr, size_t oldSize, void *newPtr, size_t newSize);

#endif /*MPSOC_MMAP_H*/