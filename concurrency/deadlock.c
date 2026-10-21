#include <stdio.h>
#include <pthread.h>

// Deadlock, like race conditions, is a problem that you have to deal with
// when doing multithreaded programming.
//
// Deadlock occurs when you have cyclical locks on one or more mutexes.
// 
// For example, suppose you have TWO mutexes: A and B. Suppose thread 1
// locks mutex A, and then mutex B. Suppose thread 2 locks mutex B, and then
// mutex A. 
//
// If you lock mutex B, then unlock mutex B, then lock mutex A, then lock
// mutex B
//
// This is an example of deadlock.
//
// Deadlock is when one or more tasks are stuck waiting on each other, such
// that none of them can proceed.
//
// Deadlock prevention and deadlock avoidance can solve deadlock.
//
// Deadlock prevention is the simple solution. It involves thing slike:
// 1. Don't do recursive locks (or, detect recursive locks)
// 2. Order your locks (i.e., don't have a cycle in your lock graph)
//
// Deadlock avoidance strategies are more complicated. Deadlock avoidance
// 	generally requires asking questions about what resources are needed
// 	by each task, conducting simulations to determine whether the tasks
// 	can run concurrently without deadlock, and permitting locks only
// 	when that's the case.
//
// Generally, in deadlock avoidance algorithms, when a task WANTS to lock
// a mutex, it doesn't simply do it. Instead, it asks the deadlock avoidance
// algorithm if doing so will cause the program to enter an unsafe state.
// If so, then the lock is not acquired. In most cases, the thread blocks.
//
// The most famous deadlock avoidance algorithm is the Banker's algorithm.
// The banker's algorithm needs to know how many of each resource each
// task will need to acquire as it runs. In the case of mutexes, the
// banker's algorithm needs to know which mutexes will be acquired by which
// threads. Whenever a task wants to acquire a resource, it asks the
// banker's algorithm if that's okay. The banker's algorithm runs a simulation.
// It analyzes all of the threads, and it considers all possible orderings in
// which said threads could acquire their remaining needed resources. If every
// possible ordering results in deadlock, then it rejects the mutex lock
// request.Otherwise, it allows it.

struct thread_input_t {
	double radius;
	double* sum_ptr;
	pthread_mutex_t* sum_mutex_ptr;
};

void* compute_volume_of_sphere_and_add_to_sum(void* thread_args) {
	struct thread_input_t* casted_arg = (struct thread_input_t*) thread_args;
	double volume = 4.0 / 3.0 * 3.14159265358979323846 * casted_arg->radius *
		casted_arg->radius * casted_arg->radius;

	pthread_mutex_lock(casted_arg->sum_mutex_ptr);
	double current_sum = *(casted_arg->sum_ptr);
	current_sum += volume;
	*(casted_arg->sum_ptr) = current_sum;
	// unlock out mutex
	// pthread_mutex_unlock(casted_arg->sum_mutex_ptr);

	// There are ways of solving this. I'll show you next week.
	return NULL;
}

int main(void) {
	pthread_t threads[100];
	struct thread_input_t all_thread_args[100];
	pthread_mutex_t sum_mutex;
	pthread_mutex_init(&sum_mutex, NULL);
	double sum = 0.0;

	for (int i = 0; i < 100; ++i) {
		all_thread_args[i].radius = i;
		all_thread_args[i].sum_ptr = &sum;
		all_thread_args[i].sum_mutex_ptr = &sum_mutex;
		int create_result = pthread_create(
			&threads[i],
			NULL,
			compute_volume_of_sphere_and_add_to_sum,
			&all_thread_args[i]
		);
		// TODO make sure it succeeded
	}

	for (int i = 0; i < 100; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf("Sum: %.3f\n", sum);

	pthread_mutex_destroy(&sum_mutex);
}
