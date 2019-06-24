//
//  NoBdProcHot.c
//  NoBdProcHot
//
//  Created by Nick on 6/24/19.
//  Copyright © 2019 Nick. All rights reserved.
//

#include <mach/mach_types.h>
#include <libkern/libkern.h>
#include <i386/proc_reg.h>

// Function that disables the BDPROCHOT
static void disable_prochot(__unused void * param_not_used) {
    wrmsr64(0x1FC, rdmsr64(0x1FC) & 0xFFFFFFFE);
}

// Function that enables the BDPROCHOT
static void enable_prochot(__unused void * param_not_used) {
    wrmsr64(0x1FC, rdmsr64(0x1FC) | 0x1);
}

kern_return_t NoBdProcHot_start(kmod_info_t * ki, void *d);
kern_return_t NoBdProcHot_stop(kmod_info_t *ki, void *d);

kern_return_t NoBdProcHot_start(kmod_info_t * ki, void *d)
{
    disable_prochot(NULL);
    printf("BDPROCHOT successfully disabled");
    return KERN_SUCCESS;
}

kern_return_t NoBdProcHot_stop(kmod_info_t *ki, void *d)
{
    enable_prochot(NULL);
    printf("BDPROCHOT successfully re-enabled");
    return KERN_SUCCESS;
}
