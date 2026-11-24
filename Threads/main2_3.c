#include <stdio.h>
#include "task2_3.c"

#include <zephyr/kernel.h>

int main(void) {
	printf("Main: Starting the threads.\n");
        printf("Main: Starting the producer.\n");

        k_thread_create(&producer_thread, producer_stack, THREAD_STACKSIZE, producer_fcn, NULL, NULL, NULL, -1, K_INHERIT_PERMS, K_NO_WAIT);

        k_thread_join(&producer_thread, K_FOREVER);

	#ifdef USERMODE_ACTIVE
		k_object_access_grant(&lab_pipe, &consumer_thread);
	#endif

	printf("Main: Producer finished. starting consumer.\n");

        k_thread_create(&consumer_thread, consumer_stack, THREAD_STACKSIZE, consumer_fcn, NULL, NULL, NULL, -1,
	#ifdef USERMODE_ACTIVE			
		K_USER | K_INHERIT_PERMS, 
	#else
		K_INHERIT_PERMS, 
	#endif
	K_NO_WAIT);

	k_thread_join(&consumer_thread, K_FOREVER);

	printf("Main: Both threads finished.\n");

        return 0;
}
