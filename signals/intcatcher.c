#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// A reentrant function is a function that can be interrupted by itself
// (i.e., while it's running, it can pause, and then another instance of
//    it starts, then ends, then the original call resumes) without causing
// issues.

volatile sig_atomic_t sigint_flag = 0;

void sigint_handler(int signo) {
	// This line of code is wrong.
	// The printf function is non-reentrant.
	// Signal handlers should only contain reentrant code.
	// printf("Hello, World!\n");
	// write(1, "Hello, World!\n", strlen("Hello, World!\n"));

	// Why is printf non-reentrant? printf (and all STDIO utilities)
	// maintain internal buffers.
	//
	// Generally, any function that modifies a global variable (or a
	// static variable, or a thread-local variable), that can, and often
	// does, destroy reentrancy.
	
	// Signal handlers must be reentrant because they can execute at ANY
	// time, including during a time at which the main application is
	// executing said non-reentrant code.
	
	// Because of the non-reentrancy problem in signal handlers,
	// signal handlers traditionally are kept EXTREMELY simple.
	
	// In this particular case, there are two solutions:
	// 1. Just use write() instead of printf()
	// 2. Instead of having the signal handler do the printing,
	// 	have it instead notify the main application that the signal
	// 	has been received, then have the main application do the
	// 	printing itself.
	
	// Typically, in order to have a signal handler communicate info back
	// to the main application, all you do is modify a global variable
	// of type volatile sig_atomic_t.
	if (sigint_flag == 0) {
		sigint_flag = 1;
	} else {
		sigint_flag = 0;
	}
}

// There's a function called sigprocmask(), and another one called
// pthread_sigmask(). These block the specified signals in the calling process
// or calling thread, respectively.

int main(void) {
	struct sigaction int_disposition;
	int_disposition.sa_handler = sigint_handler;
	// int_disposition.sa_handler = SIG_IGN; // This is the ignore disposition
	// int_disposition.sa_handler = SIG_DFL; // This is the default disposition

	int_disposition.sa_flags = 0;

	// There are four functions for manipulating sigset_t variables:
	// sigfillset(sigset_t*): Fills the signal set with all signal numbers
	// sigemptyset(sigset_t*): Empties the signal set of all signal numbers
	// sigaddset(sigset_t*, int signo): Adds the specified signal number
	// 	to the specified signal set
	// sigdelset(sigset_t*, int signo): Removes the specified signal number
	// 	from the specified signal set
	sigemptyset(&int_disposition.sa_mask);
	// sigaddset(&int_disposition.sa_mask, SIGINT); // This is technically
	// unnecessary, because by default, a signal number will always
	// be added to its own sa_mask signal set

	sigaction(SIGINT, &int_disposition, NULL);

	while(1) {
		sleep(1);
		printf("Goodbye, World!\n");

		if (sigint_flag == 0) {
			// NOT foreground-only mode. Proceeed to parse
			// & if present, and send command to the background.
		} else {
			// ARE in foreground-only mode. Ignore & if present.
			// Run all commands in the foreground.
		}
	}
}
