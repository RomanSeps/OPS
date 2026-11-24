/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>


#include "task1_5.c"

int main(void){
	int64_t start = k_uptime_get();

	printf("Main: Starting the threads.\n");
        printf("Main: Starting the producer.\n");

        k_thread_create(&producer_thread, producer_stack, THREAD_STACKSIZE, producer_fcn, NULL, NULL, NULL, -1, K_INHERIT_PERMS, K_NO_WAIT);

        k_thread_join(&producer_thread, K_FOREVER);

	printf("Main: Producer finished after %lld ms, starting consumer.\n", k_uptime_get() - start);

        k_thread_create(&consumer_thread, consumer_stack, THREAD_STACKSIZE, consumer_fcn, NULL, NULL, NULL, -1, K_INHERIT_PERMS, K_NO_WAIT);

	k_thread_join(&consumer_thread, K_FOREVER);

	printf("Main: Both threads finished after %lld ms.\n", k_uptime_get() - start);

        return 0;
}

