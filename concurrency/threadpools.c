// A very common strategy in multithreading is to create a thread pool
// at the start of the application. All of these N threads simply do the
// following:
//
// 1. Wait until a) a shared queue of tasks is NOT empty, or b) the queue
// 	is said to be "closed". A closed queue is a queue which will have
// 	no more tasks added to it, ever.
// 2. If the queue is not empty, dequeue a task from the queue, and carry it out
//    Else, we terminate
// 3. Repeat from step 1
//
// At the same time, the main thread will occasionally add tasks to the queue,
// representing work that needs to be done.
//
// There are very good reasons to decouple your tasks from your threads.
// 1. Creating threads is particularly expensive.
// 2. System calls are somewhat expensive. In particular, pthread_mutex_lock()
// 	and pthread_mutex_unlock() are going to be called a lot by every
// 	thread.
// 3. The more threads you have competing for the same shared resource,
// 	the more resource contention you have.
// 4. The more threads you have, the more time the CPU scheduler will spend
//    rotating them in and out of the CPU. These context switches are
//    expensive.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// A structure of this type represents some work that needs to be done.
struct task {
	int number;
};

struct task_queue {
	struct task* tasks;
	size_t n_tasks;
	pthread_mutex_t mutex;
	pthread_cond_t cv;
	_Bool closed;
};

int init_task_queue(struct task_queue* queue) {
	queue->tasks = NULL;
	queue->n_tasks = 0;
	queue->closed = 0;
	
	int error = pthread_mutex_init(&queue->mutex, NULL);
	if (error) {
		return error;
	}

	error = pthread_cond_init(&queue->cv, NULL);
	if (error) {
		pthread_mutex_destroy(&queue->mutex);
		return error;
	}

	return 0;
}

void enqueue_task(struct task_queue* queue, const struct task* t) {
	pthread_mutex_lock(&queue->mutex);

	queue->tasks = realloc(queue->tasks, sizeof(struct task) * (queue->n_tasks + 1));
	++queue->n_tasks;
	queue->tasks[queue->n_tasks - 1] = *t;

	pthread_mutex_unlock(&queue->mutex);
	pthread_cond_signal(&queue->cv);
}

int dequeue_task(struct task_queue* queue, struct task* t) {
	pthread_mutex_lock(&queue->mutex);
	while (queue->n_tasks == 0 && !queue->closed) {
		pthread_cond_wait(&queue->cv, &queue->mutex);
	}

	if (queue->n_tasks == 0) {
		pthread_mutex_unlock(&queue->mutex);
		return 1;
	}

	*t = queue->tasks[0];

	memmove(queue->tasks, &queue->tasks[1], sizeof(struct task) * (queue->n_tasks - 1));
	--queue->n_tasks;
	// queue->tasks = realloc(queue->tasks, sizeof(struct task) * queue->n_tasks);

	pthread_mutex_unlock(&queue->mutex);

	return 0;
}

int process_task(const struct task* t) {
	for (int i = 2; i < t->number; ++i) {
		if (t->number % i == 0) {
			return 0;
		}
	}

	return 1;
}

void close_queue(struct task_queue* queue) {
	pthread_mutex_lock(&queue->mutex);
	queue->closed = 1;
	pthread_mutex_unlock(&queue->mutex);
	pthread_cond_broadcast(&queue->cv);
}

void* process_tasks(void* thread_args) {
	struct task_queue* queue = (struct task_queue*) thread_args;

	struct task task_to_be_executed;
	int failed_to_dequeue_task = 0;
	do {
		failed_to_dequeue_task = dequeue_task(queue, &task_to_be_executed);
		if (!failed_to_dequeue_task) {
			printf("%d\n", process_task(&task_to_be_executed));
		}
	} while(!failed_to_dequeue_task);

	return NULL;
}

void free_task_queue(struct task_queue* queue) {
	free(queue->tasks);
	queue->tasks = NULL;
	queue->n_tasks = 0;
	queue->closed = 0;
	pthread_mutex_destroy(&queue->mutex);
	pthread_cond_destroy(&queue->cv);
}

int main(void) {
	struct task_queue queue;
	int error = init_task_queue(&queue);
	if (error) {
		printf("Error: Failed to initialize task queue\n");
		return 1;
	}

	pthread_t thread_pool[100];
	for (int i = 0; i < 100; ++i) {
		error = pthread_create(&thread_pool[i], NULL, process_tasks, &queue);

		if (error) {
			printf("Error: Failed to create one or more threads\n");
			return 1;
		}
	}

	for (int i = 1; i <= 10000; ++i) {
		struct task t = {i};
		enqueue_task(&queue, &t);
	}

	close_queue(&queue);

	// When the main thread terminates, the whole process terminates.
	for (int i = 0; i < 100; ++i) {
		pthread_join(thread_pool[i], NULL);
	}

	free_task_queue(&queue);
}
