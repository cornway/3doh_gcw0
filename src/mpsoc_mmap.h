
#ifndef MPSOC_MMAP_H
#define MPSOC_MMAP_H

void *mpsoc_mmap_shared (int *_fd);
void mpsoc_unmap_shared (int fd);
void mpsoc_memset(void *_buf, int val, size_t size);
void *mpsoc_mmap (uint64_t paddr, uint64_t psize);

#endif /*MPSOC_MMAP_H*/