#include <stdio.h>
#include <pthread.h>

// The last access control mechanism is condition variables.

// A condition variable is a thing that supports two operations:
// 1. Wait on the condition variable until signaled
// 	Any time a condition variable is waited on, the mutex is
// 	automatically unlocked. Implication, the mutex MUST be locked
// 	at the time that you call pthread_cond_wait(). Whenever
// 	pthread_cond_wait() wakes up, it automatically relocks the mutex.
// 2. Signal waiter(s) on the condition variable.
// 	2.a. Signal ONE waiter
// 	2.b. Signal ALL waiters (broadcasting)
// 
// You MUST pair a condition variable with a mutex.
//
// The general pattern for using a condition variable is as follows:
//
// In the waiting thread:
// lock the mutex associated with the condition variable
// while (some condition is occurring) {
//     wait on the condition variable (unlocks the mutex implicitly, then
//     		waits, then relocks it)
// }
// maybe some other operations that involve the shared resource(s)
// unlock the mutex
//
// In some other thread:
// 
// lock the mutex associated with the condition variable
// modify one or more shared resources that change the
// 	current state of the condition that the waiting
// 	thread is waiting on
// unlock the mutex
// signal the condition variable (or broadcast)

struct thread_input_t {
	float* the_variable;
	pthread_mutex_t* mutex;
	pthread_cond_t* cv;
};

void* start_routine(void* thread_args) {
	struct thread_input_t* casted_args = (struct thread_input_t*) thread_args;

	// The secondary thread will be our waiter.
	
	pthread_mutex_lock(casted_args->mutex);
	
	while (*(casted_args->the_variable) < 10) {
		// pthread_cond_wait() implicitly unlocks the mutex,
		// waits until signaled (or otherwise woken up), then
		// relocks the mutex
		pthread_cond_wait(casted_args->cv, casted_args->mutex);
	}
	pthread_mutex_unlock(casted_args->mutex);

	printf("Hello, World!\n");

	return NULL;
}

int main(void) {
	float the_variable = 0.0;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_t cv;
	pthread_cond_init(&cv, NULL);
	pthread_t thread;

	struct thread_input_t thread_args;
	thread_args.the_variable = &the_variable;
	thread_args.mutex = &mutex;
	thread_args.cv = &cv;

	int result = pthread_create(&thread, NULL, start_routine, &thread_args);
	if (result) {
		printf("pthread_create failed\n");
	}

	// The main thread will modify the_variable, and signal the
	// secondary thread (waiter) to recheck its condition
	pthread_mutex_lock(&mutex);
	the_variable += 20.0;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cv); // Signals a single random waiting thread
	// pthread_cond_broadcast(&cv); // Signals all waiting threads

	pthread_join(thread, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cv);


}
