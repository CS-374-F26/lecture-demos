#include <stdio.h>
#include <pthread.h>

void* print_hello(void* thread_args) {
	printf("Hello\n");
	return NULL;
}

int main(void) {
	// When you create a new POSIX kernel thread,
	// you have to specify the function that you want the kernel
	// thread to execute.
	
	// Create a variable of type pthread_t
	pthread_t my_thread;
	
	// Call pthread_create
	// 1. pthread_t
	// 2. attributes (NULL)
	// 3. start_routine pointer
	int create_result = pthread_create(&my_thread, NULL, print_hello, NULL);

	// What's a void pointer? A pointer to SOMETHING.
	// Basically, the only thing that you can do to a void pointer
	// is cast it to the more specific, correct pointer type, of the thing
	// that it actually points to.
	
	// When a kernel thread is created, it IMMEDIATELY starts running
	// its start routine. When its start routine finishes, so too does
	// the thread.
	
	// However, when the main thread terminates, the entire process
	// terminates. This is the special thing about the main thread.
	// When the process terminates, the kernel automatically terminates
	// any still-running secondary threads.
	
	// Probably, we want a little bit of thread synchronization.
	// Basically, I want to tell the main thread to wait until the
	// secondary thread has terminated, before the main thread itself
	// terminates.
	//
	
	// We're going to feed two birds with one scone, we're going to
	// synchronize and clean up at the same time.
	//
	// There are two ways to clean up a dead thread's resources (you must
	// do one of these two things to every thread you create):
	// 1) join the thread. Tells the joining thread to wait until the joined
	// 	thread is done executing. Then, it immediately cleans up
	// 	the underlying resources of the joined thread. It also
	// 	gives you access to the return value of the joined thread's
	// 	start routine.
	// 2) detach the thread. Tells the operating system kernel to automatically
	//    and asynchronously clean up the detached thread's resources once
	//    it's done executing.
	
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
	
}
