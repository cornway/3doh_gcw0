#ifndef MPSOC_INFRA_H
#define MPSOC_INFRA_H

typedef struct {
    void *dev;
    void *io;
} mpsoc_dev_t;

int mpsoc_infra_init (void);
int mpsoc_infra_close (void);
void *mpsoc_dev_open(const char *dev_name);
void mpsoc_dev_close(void *dev);
void *mpsoc_dev_io(const void *_dev);

#endif /*MPSOC_INFRA_H*/
