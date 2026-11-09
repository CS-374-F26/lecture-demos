#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

void print_hello(int signo) {
	write(1, "Hello, World!\n", strlen("Hello, World!\n"));
}

int main(void) {
	// Suppose a process modifies its disposition for some signal number,
	// and then forks a child process:
	struct sigaction disposition_info;
	disposition_info.sa_handler = print_hello;
	sigfillset(&disposition_info.sa_mask);
	disposition_info.sa_flags = 0;
	sigaction(SIGINT, &disposition_info, NULL);
	
	disposition_info.sa_handler = SIG_IGN;
	sigfillset(&disposition_info.sa_mask);
	disposition_info.sa_flags = 0;
	sigaction(SIGTSTP, &disposition_info, NULL);

	pid_t fork_result = fork();
	if (fork_result == 0) {
		// This is the child process

		// What is the child process's disposition for SIGTSTP?
		//
		// A: SIG_IGN.
		//
		// When you fork a child process, it inherits its parent's
		// dispositions for all signals.

		// These dispositions are only COPIES. You can modify one
		// process's dispositions without modifying the other process's
		// dispositions.

		pause();
		printf("Child!\n");

		// What happens if the child process, say, runs another
		// program via execXXX()?
		execlp("sleep", "sleep", "100", NULL);

		// Suppose that while the child process is running the
		// system command "sleep 100", we press CTRL+C.

		// Remember: execXXX() rewrite the process's virtual address
		// space with the contents of a completely new program.

		// As such, the child process does not have a copy of
		// print_hello (the signal handler).
		//
		// The rule is this: execXXX() calls will reset
		// custom signal handling dispositions to SIG_DFL.
		// It does NOT reset SIG_IGN dispositions to SIG_DFL.

		// When the child starts sleep 100, its SIGINT disposition
		// will immediately reset to SIG_DFL. When we press CTRL+C,
		// that will send it SIGINT, which will cause the child to
		// terminate.
	} else {
		// This is the parent process, and fork_result stores
		// the PID of the forked child process
		
		pause();
		printf("Parent!\n");

		int termination_info;
		wait(&termination_info);

		printf("Parent is now done!\n");
	}
}
