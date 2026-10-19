#include <stdio.h>
#include <pthread.h>


// ATM race condition example:
// 1. You go to the ATM, and you send your friend to another ATM
// 2. You withdraw $10 from your account on your ATM
// 3. At the same time, your friend withdraws $10 from your account
// 	at their ATM
//
// Suppose:
// 1. Your ATM retrieves the current balance in your account
// 2. Your ATM then subtracts 10 from that balance
// 3. Your friend's ATM retrieves the current balance in your account
// 4. Your friend's ATM subtracts 10 from that balance
// 5. Your ATM updates your account balance to match the newly computed difference
// 	(from step 2)
// 6. Your friend's ATM updates your account balance to match the newly computed
// 	difference (from step 4)
// 7. Both ATMs then dispense $10 bills
// 8. Q: What is the balance of your account compared to how it started? $10
// 	less than when you started.

struct thread_input_t {
	double radius;
	double* sum_ptr;
	pthread_mutex_t* sum_mutex_ptr;
};

// A race condition is a problem that occurs when two or more concurrent
// tasks access the same shared resource, AT LEAST ONE of them updates said
// shared resource, and they aren't properly synchronized.
//
// The two main ways of solving race condition issues are
// atomic operations, and access control.

// There are various access control mechanisms:
// Mutexes
// Semaphores -> binary semaphores, counting semaphores
// Condition variables


// A mutex is lock that can only be acquired by one task at a time.
// In the simplest case, if a mutex is locked by one task, and then another
// task tries to lock it, the second task will block (wait, get stuck,
// freeze, hang) until the first task unlocked the mutex.
// In most mutex implementations, only the task that locked the mutex
// most recently is allowed to unlock it.
//
// If two or more tasks are simultaneously blocking on a mutex lock,
// then when it is unlocked, one of the two blocking tasks will lock it.
// But WHICH of those two tasks gets to lock it is usually arbitrary.
//
// You can absolutely use mutexes to solve race conditions.
//
// General strategy:
//
// 1. Identify critical sections. Regions of code where it's imperative
// 	that the executing thread doesn't get interrupted by other critical
// 	sections, perhaps of other threads.
// 2. At the beginning of every critical section, you lock the mutex.
// 	(Generally, each set of closely related shared resources gets a
// 	single mutex dedicated to it).
// 3. At the end of every critical section, you unlock the mutex.

void* compute_volume_of_sphere_and_add_to_sum(void* thread_args) {
	struct thread_input_t* casted_arg = (struct thread_input_t*) thread_args;
	double volume = 4.0 / 3.0 * 3.14159265358979323846 * casted_arg->radius *
		casted_arg->radius * casted_arg->radius;
	// A race condition can occur here. This thread might read the current
	// sum value from main, compute a new value, get interrupted, and then
	// assign the new computed value to sum in main once it gets time
	// in the CPU again. But during that interruption period, sum might
	// be updated by other threads, and this thread isn't aware of those
	// updates. Its final assignment will overwrite those changes.
	
	// lock our mutex
	//
	// Contention describes a scenario where two or more tasks
	// are trying to access the same shared resource but must
	// wait on one another due to access control.
	pthread_mutex_lock(casted_arg->sum_mutex_ptr);
	double current_sum = *(casted_arg->sum_ptr);
	current_sum += volume;
	*(casted_arg->sum_ptr) = current_sum;
	// unlock out mutex
	pthread_mutex_unlock(casted_arg->sum_mutex_ptr);

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
