/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <display/mb_display.h>

#include "uart_driver.h"
#include "at.h"

void main(void)
{
    printk("hello world!\n");

    DriverOpen();
    DriverSetCallback(ATCommandParser);
    /* Note: the k_sleep() calls after mb_display_print() and
     * mb_display_image() are not normally needed since the APIs
     * are used in an asynchronous manner. The k_sleep() calls
     * are used here so the APIs can be sequentially demonstrated
     * through this single main function.
     */

    while(1) {
        k_sleep(K_MSEC(250));
    }
}
