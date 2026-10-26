// A process is a running instance of a program.
//
// Every process has a bunch of data associated with it:
//   1. PID (Process's ID). Unique integer.
//   2. PPID (Process's parent's ID)
//   3. Environment
//   	 a. User ID (UID): The ID of the running user
//   	 b. Group ID (GID): The ID of the running group
//   	 c. Environment variables: string variables (key-value pairs)
//   	 d. Working directory (chdir(), cd)
//   4. Virtual address space.
//        Mapping from virtual memory addresses to physical memory addresses.
//        0x0004.

#include <unistd.h>
#include <stdio.h>

int main(void) {
	// In *nix systems, processes are created from other processes.
	// They do this by forking child processes.
	
	// When one process creates another process, the creator is the
	// parent, and the created process is the child. Processes
	// in *nix systems form a family tree.
	
	// When a Linux system first boots, the kernel creates
	// an init process (with PID 1). The init process is the root of
	// the process tree.
	
	// Processes can, of course, run concurrently.
	
	// The CPU scheduler context switches between kernel threads.
	// Remember: Every process has at least one kernel thread: the main
	// thread, which runs the process's main function.
	
	// When a process A forks (creates) a child process B, B is initially
	// a near-identical replica of A. There is a slight distinction
	// between A and B, which allows them to distinguish themselves from
	// one another. You can detect this distinction with an if statement,
	// then have the two processes go off and do different things.
	
	pid_t fork_result = fork();

	if (fork_result == 0) {
		// I am the child process
		printf("I am the child\n");

		// It is possible for the child process to load a new
		// program executable into its virtual address space
		// and execute its entry point (main()).
		//
		// But we'll get to that on Wednesday.
	} else if (fork_result > 0) {
		// I am the parent process
		printf("I am the parent\n");

		// When a child process is created, it is the parent's
		// responsibility to clean it up from the system (eventually).
		
		// Specifically, a given process is always in one of
		// four states:
		// 1. Running
		// 2. Runnable (waiting)
		// 3. Zombie
		// 4. Another one I'm forgetting. I'll tell you on Wednesday.

		// A zombie process is a process that has terminated but has
		// not yet been cleaned up by its parent. Zombie processes
		// are dead, but they're still lingering within the kernel's
		// data structures.

		// Unlike threads, there isn't a simple way to detach a process.
		// Instead, typically, child processes are cleaned up
		// by waitpid() or wait().
		//
		// waitpid() is similar to pthread_join(), but for processes.
		// It's given the PID of a CHILD PROCESS to wait for. It
		// waits for that child to terminate. Then it cleans it up
		// from the kernel's internal storage. It can ONLY be done
		// from within the child process's parent process. This at
		// least is how waitpid() works in its default configuration.

		// 
	} else {
		// I am the parent, but fork() failed, so no child process
		// was created.
		
	}

	printf("Hello, World!\n");
	printf("Goodbye, World!\n");
}
