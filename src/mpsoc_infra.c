
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <metal/sys.h>
#include <metal/irq.h>
#include <metal/sleep.h>
#include <metal/alloc.h>
#include <metal/device.h>

#include <mpsoc_infra.h>

static FILE *fp_log;

//a0000000.axi_bram_ctrl
///amba_pl@0/axi_bram_ctrl@a0100000

static const char *symbols_path = "/sys/firmware/devicetree/base/__symbols__/";

static char *symbol_to_dts (char *dtsnode, const char *symbol_name)
{
    char buf[PATH_MAX], fpath[PATH_MAX], *match;
    char *dtsname;
    FILE *fp;

    mpsoc_log("Opening %s\n", symbol_name);

    sprintf(fpath, "%s%s", symbols_path, symbol_name);
    fp = fopen(fpath, "r");

    if (NULL == fp) {
        mpsoc_log("Failed to open file %s\n", fpath);
        return NULL;        
    }

    if (fgets(buf, sizeof(buf), fp) == NULL) {
        mpsoc_log("Failed to read file %s\n", fpath);
        return NULL;
    }

    match = strstr(buf, "amba_pl@0/");
    if (match) {
        match += strlen("amba_pl@0/");
        dtsname = match;
        match = strchr(match, '@');
    }
    if (NULL == match) {
        mpsoc_log("Failed to lookup symbol name %s\n", symbol_name);
        return NULL;
    }

    match[0] = '\0';
    match += strlen("@");

    sprintf(dtsnode, "%s.%s", match, dtsname);

    fclose(fp);

    mpsoc_log("Got dtsnode = %s\n", dtsnode);

    return dtsnode;
}

static void mpsoc_infra_init_log (void)
{
    fp_log = fopen("3doh.log", "w");
}

void mpsoc_log (const char * format, ...)
{
  va_list args;
  va_start (args, format);
  vfprintf (fp_log, format, args);
  vfprintf (stdout, format, args);
  va_end (args);
}

static void mpsoc_infra_deinit_log (void)
{
    fclose(fp_log);
}

void mpsoc_metal_log_handler(enum metal_log_level level,
			       const char *format, ...)
{
	char msg[1024];
	va_list args;
	static const char * const level_strs[] = {
		"metal: emergency: ",
		"metal: alert:     ",
		"metal: critical:  ",
		"metal: error:     ",
		"metal: warning:   ",
		"metal: notice:    ",
		"metal: info:      ",
		"metal: debug:     ",
	};

	va_start(args, format);
	vsnprintf(msg, sizeof(msg), format, args);
	va_end(args);

	if (level <= METAL_LOG_EMERGENCY || level > METAL_LOG_DEBUG)
		level = METAL_LOG_EMERGENCY;

	fprintf(fp_log, "%s%s", level_strs[level], msg);
    fprintf(stdout, "%s%s", level_strs[level], msg);
}

int mpsoc_infra_init (void)
{
    struct metal_init_params init_param = {.log_handler = mpsoc_metal_log_handler, .log_level = METAL_LOG_DEBUG};

    mpsoc_infra_init_log();

    if (metal_init(&init_param)) {
		printf("ERROR: Failed to run metal initialization\n");
		exit(-1);
	}
    metal_set_log_level(METAL_LOG_DEBUG);

    return 0;
}

int mpsoc_infra_close (void)
{
    metal_finish();
    mpsoc_infra_deinit_log();
    return 0;
}

void mpsoc_abort (void)
{
    mpsoc_infra_close();
    exit(1);
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
    int status;
    uint32_t reg[4];
    uint64_t paddr, psize;
    struct metal_device *dev = (struct metal_device *)_dev;
    void *vptr = NULL;

    void *io = metal_device_io_region(dev, 0);

    if (io == NULL) {
		metal_log(METAL_LOG_ERROR, "\n Failed to map IO region for %s.\n", dev->name);
        return NULL;
    }

    status = metal_linux_get_device_property(dev, "reg",
									 reg, sizeof(reg));

    for (int i  = 0; i < sizeof(reg)/sizeof(reg[0]); i++) {
        reg[i] = ntohl(reg[i]);
    }
    paddr = ((uint64_t)reg[0] << 32) | reg[1];
    psize = ((uint64_t)reg[2] << 32) | reg[3];

    vptr = mpsoc_mmap(paddr, psize);

    mpsoc_log("mpsoc_dev_io: paddr=%x psize=%x vaddr=%x\n", paddr, psize, vptr);

    return vptr;
}