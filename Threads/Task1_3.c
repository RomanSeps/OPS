
/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

#define STACK_SIZE 500
#define PRIORITY 5 
#define SLEEP_TIME 500

#define TL1_MESSAGE "1: I am the first thread!"
#define TL2_MESSAGE "2: I am the second thread!"

void entry_point(k_timeout_t* tl_sleep, const char tl_message[]) {
	
	while (true) {
		printf("%s\n", tl_message);
		k_sleep(*tl_sleep);
	}
}

	const char tl1_message[50] = TL1_MESSAGE;
	const char tl2_message[50] = TL2_MESSAGE;

	k_timeout_t tl1_sleep = K_MSEC(SLEEP_TIME);
	k_timeout_t tl2_sleep = K_MSEC(SLEEP_TIME);


	K_THREAD_DEFINE(tl1_tid, STACK_SIZE, entry_point, &tl1_sleep, tl1_message, NULL, PRIORITY, 0, 0);
	K_THREAD_DEFINE(tl2_tid, STACK_SIZE, entry_point, &tl2_sleep, tl2_message, NULL, PRIORITY, 0, 0);
