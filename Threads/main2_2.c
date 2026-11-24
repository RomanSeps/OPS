#include <stdio.h>
#include "task2_2.c"

#include <zephyr/kernel.h>

int main(void) {
	printf("Main: Starting threads now.\n");
	printf("Main: Creating kernel-space thread\n");

	k_thread_create(&kernelspace_thread, kernelspace_stack, THREAD_STACKSIZE,
			kernelspace_thread_fcn, NULL, NULL, NULL,
			-1, K_INHERIT_PERMS, K_NO_WAIT);

	k_sleep(K_MSEC(1000));

	printf("Main: Creating user-space thread\n");

	k_thread_create(&userspace_thread, userspace_stack, THREAD_STACKSIZE,
			userspace_thread_fcn, NULL, NULL, NULL,
			-1, K_USER | K_INHERIT_PERMS, K_NO_WAIT);
	return 0;
}
