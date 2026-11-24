#include <stdio.h>

#include <zephyr/kernel.h>

#define THREAD_STACKSIZE 1024

#define MAIN_SLEEP 5000 

#define PIPE_SIZE 100
#define PIPE_MESSAGE "Producer: Hello world!"

#define PRODUCER_WORK_MS 2000



K_THREAD_STACK_DEFINE(producer_stack, THREAD_STACKSIZE);
K_THREAD_STACK_DEFINE(consumer_stack, THREAD_STACKSIZE);


struct k_thread producer_thread;
struct k_thread consumer_thread;


K_PIPE_DEFINE(lab_pipe, PIPE_SIZE, 4);


void producer_fcn(void *p1, void *p2, void *p3){
	unsigned char *data;
	size_t total_size;
	int bytes_written;

	printf("Producer is starting.\n");
	k_sleep(K_MSEC(PRODUCER_WORK_MS));
	
	data = (unsigned char *) PIPE_MESSAGE;
	total_size = sizeof(PIPE_MESSAGE);

	printf("Producer: Sending %s.\n", data);
	printf("Producer: Sending %d bytes.\n", total_size);

	bytes_written = k_pipe_write(&lab_pipe, data, total_size, K_NO_WAIT);

	if (bytes_written < 0) {
		printf("Producer: Error writing to the pipe.\n");
		return;
	}else if ((size_t) bytes_written != total_size) {
		printf("Producer: Not all data sent!\n");
		return;
	}else {
		printf("Producer: Data sent successfully.\n");
	}
}

void consumer_fcn(void *p1, void *p2, void *p3){
	unsigned char buffer[100];
	int bytes_read;
	
	printf("Consumer is starting.\n");
	bytes_read = k_pipe_read(&lab_pipe, buffer, sizeof(buffer), K_NO_WAIT);
	
	if (bytes_read < 0){
		printf("Consumer: Error reading from pipe.\n");
		return;
	}else if (bytes_read == 0){
		printf("Consumer: No data to read.\n");
		return;
	}else{
		printf("Consumer: Data read successfully.\n");
	}

	printf("Consumer: %d bytes read.\n", bytes_read);
	for (int i = 0; i < bytes_read; i++) {
		printf("Consumer: %c was in pipe.\n", buffer[i]);
	}
}

