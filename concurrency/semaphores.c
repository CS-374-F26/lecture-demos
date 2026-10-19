#include <stdio.h>
#include <pthread.h>
#include <semaphore.h> // Provides sem_t, and various functions


// Mutex stands for mutual exclusion semaphore

// Mutexes are one form of access control.
//
// Another one is known as semaphores.
//
// A sempahore is an integer that can be initialized to any non-negative
// value. Then, you can do two things to it:"
// 1. Increment it (sem give, or sem post)
// 2. Decrement it (sem take, or sem wait).
// 	A semaphore can never drop below zero. If a task tries to decrement
// 		a semaphore, and that would cause it to become negative,
// 		the task will block (wait, freeze, hang) until the semaphore
// 		is incremented.
//
// If two tasks try to decrement the same semaphore at the same time,
// and the combination of those decrements would cause it to drop below
// zero, then only one succeeds.
//
// There are two main categories of use cases for semaphores:
// 1. Binary semaphores
// 	a. Flagging semaphore. You initialize the semaphore to zero.
// 		In one task, you decrement it at some point.
// 		In another task, you increment it at some point.
// 	b. Mutexes: You initialize the semaphore to one. At the start
// 		of every critical section, you decrement the semaphore.
// 		At the end of every critical section, you increment
// 		the semaphore.
// 2. Counting semaphores. You initialize the semaphore to some count N
// 	representing the number of instances of a given shared resource
// 	that you have. Whenever a task wants to allocate / use one of
// 	the shared resources in the pool, it decrements the sempahore.
// 	When a task is done using its instance of the shared resource,
// 	it releases it back to the pool by incrementing the semaphore.
// 	(It is okay if it gets incremented externally).

// Thread A:
// Op 1
// 2
// 3
// 4
// decrement semaphore
// 5
// 6
//
//
// Thread B:
// Op 1
// 2
// increment semaphore
// 3

double result;

struct thread_inputs_t {
	sem_t* my_semaphore_ptr;
};

void* calculate(void* thread_args) {
	struct thread_inputs_t* casted_args =
		(struct thread_inputs_t*) thread_args;
	printf("Hello, ");
	result = 4.0 / 3.0 * 3.141592 * 9.81 * 9.81 * 9.81;
	// Increment semaphore
	sem_post(casted_args->my_semaphore_ptr);
	printf("World\n");
	return NULL;
}

int main(void) {
	sem_t my_semaphore;
	// The second argument is an integer called pshared.
	sem_init(&my_semaphore, 0, 0);
	pthread_t my_thread;

	struct thread_inputs_t my_inputs;
	my_inputs.my_semaphore_ptr = &my_semaphore;
	
	int create_result = pthread_create(&my_thread, NULL, calculate, &my_inputs);



	printf("Goodbye\n");
	printf("The purple cow croaks at midnight\n");
	printf("Eat more beef kick less cats\n");

	// decrement semaphore
	sem_wait(&my_semaphore);

	printf("Result computed by thread B: %.3lf\n", result);


	void* p = NULL;
	pthread_join(my_thread, &p);

	// Alternative to pthread_join. Asynchronous / non-blocking, does not
	// synchronize. Also makes it impossible to ever access the return
	// value of the detached thread.
	// pthread_detach(my_thread);
	
	// There's also:
	// pthread_cancel(): This can be called from one thread to suddenly
	// 	terminate another thread. Usually a bad idea.
	// pthread_exit(): This exits the calling thread. Usually a bad idea.
	// pthread_self(): This function returns a pthread_t value representing
	// 	the calling thread.
	// pthread_equal(): This takes two pthread_t values and returns a
	// 	nonzero value (true) if they represent the same kernel thread,
	// 	or 0 (false) otherwise.
	
	sem_destroy(&my_semaphore);
}
