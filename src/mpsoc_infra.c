
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <metal/sys.h>
#include <metal/irq.h>
#include <metal/sleep.h>
#include <metal/alloc.h>
#include <metal/device.h>

//a0000000.axi_bram_ctrl
///amba_pl@0/axi_bram_ctrl@a0100000

static const char *symbols_path = "/sys/firmware/devicetree/base/__symbols__/";

static char *symbol_to_dts (char *dtsnode, const char *symbol_name)
{
    char buf[PATH_MAX], fpath[PATH_MAX], *match;
    char *dtsname;
    FILE *fp;

    printf("Opening %s\n", symbol_name);

    sprintf(fpath, "%s%s", symbols_path, symbol_name);
    fp = fopen(fpath, "r");

    if (NULL == fp) {
        printf("Failed to open file %s\n", fpath);
        return NULL;        
    }

    if (fgets(buf, sizeof(buf), fp) == NULL) {
        printf("Failed to read file %s\n", fpath);
        return NULL;
    }

    match = strstr(buf, "amba_pl@0/");
    if (match) {
        match += strlen("amba_pl@0/");
        dtsname = match;
        match = strchr(match, '@');
    }
    if (NULL == match) {
        printf("Failed to lookup symbol name %s\n", symbol_name);
        return NULL;
    }

    match[0] = '\0';
    match += strlen("@");

    sprintf(dtsnode, "%s.%s", match, dtsname);

    fclose(fp);

    printf("Got dtsnode = %s\n", dtsnode);

    return dtsnode;
}

int mpsoc_infra_init (void)
{
    struct metal_init_params init_param = METAL_INIT_DEFAULTS;

    if (metal_init(&init_param)) {
		printf("ERROR: Failed to run metal initialization\n");
		return -1;
	}
    metal_set_log_level(METAL_LOG_DEBUG);
}

int mpsoc_infra_close (void)
{
    metal_finish();
    return 0;
}

void *mpsoc_dev_open(const char *dev_name)
{
    char dtsnode[PATH_MAX];
    struct metal_device *dev;
    uint32_t status;

    if (NULL == symbol_to_dts(dtsnode, dev_name)) {
        return NULL;
    }

    status = metal_device_open("platform", dtsnode, &dev);
    if (status) {
        metal_log(METAL_LOG_ERROR, "\n Failed to open device %s\n", dtsnode);
        return NULL;
    }
    return dev;
}

void mpsoc_dev_close(void *dev)
{
    metal_device_close(dev);
}

void *mpsoc_dev_io(const void *_dev)
{
    struct metal_device *dev = (struct metal_device *)_dev;
    void *io = metal_device_io_region(dev, 0);

    if (io == NULL) {
		metal_log(METAL_LOG_ERROR, "\n Failed to map RFDC region for %s.\n", dev->name);
	}
    return io;
}