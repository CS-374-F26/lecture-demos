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
#include <sys/wait.h>
#include <stdlib.h> // exit()

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
	
	// Processes have their own virtual address spaces. So the two processes
	// have separate copies of x (and all other variables)
	int x = 5;
	
	// A process has environment variables. By default, a child process
	// will inherit the environment variables of its parent when created.
	
	// You can modify environment variables using putenv("NAME=VALUE")
	putenv("HOME=/home/a-different-user");
	
	pid_t fork_result = fork();

	// Even though the child gets an apparent copy of all the variables
	// from its parent, it's actually quite fast due to a technique
	// known as copy-on-write (CoW). When the child is first created,
	// the child gets its own page table, with its own mapping into
	// physical memory. However, initially, the child's page table
	// is identical to its parent's. They map to the same physical memory.
	// So initially, the processes' virtual pages map to the same
	// physical pages. These hypothetical (terrible) lines of code
	// would reach into the same place in physical RAM:
	// int* ptr = 0x0007;
	// printf("%d\n", *ptr);
	// However, the moment either process tries to MODIFY memory in one
	// of its virtual pages, then the page is copied, and both processes'
	// entries for that page are updated in their respective page tables.
	// So, this would update the two processes' page tables so that their
	// entries for 0x0007 now point to two different physical pages.
	// It does this by copying the physical page before conducting the
	// modification.
	// *ptr = 20;

	if (fork_result == 0) {
		// I am the child process
		// printf("I am the child\n");
		// Changes the child's x to 6, but the parent's x is still 5
		x = 6;

		// You can get environment variables using getenv()
		char* home = getenv("HOME");
		printf("%s\n", home);

		// It is possible for the child process to load a new
		// program executable into its virtual address space
		// and execute its entry point (main()).
		
		// We can do this with exec-family functions.
		char* argv[] = {
			"ls",
			"--color=auto",
			"some_directory",
			NULL
		};
		execvp(argv[0], argv);

		// execlp("lsss", "lsss", "--color=auto", "some_directory", NULL);

		// If exec()-family functions succeed, they rewrite the
		// virtual address space, and THIS PROGRAM is considered
		// over / terminated within the child process.

		// However, if an exec()-family function fails, then the
		// child process will continue executing THIS program.

		// A very common strategy:
		exit(1);
	} else if (fork_result > 0) {
		// I am the parent process
		// printf("I am the parent\n");

		// When a child process is created, it is the parent's
		// responsibility to clean it up from the system (eventually).
		
		// Specifically, a given process is always in one of
		// four states:
		// 1. Running / runnable (the process is currently running
		// 	on the CPU, OR it's just waiting for the CPU scheduler
		// 	to give it some time to run)
		// 2. Waiting (waiting for some external event to wake it up)
		// 3. Zombie
		// 4. Stopped (paused).

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

		int term_information;
		// waitpid waits for the given child process to terminate,
		// cleans it up, harvests its termination info, and stores it
		// in the int referenced by the second (pointer) argument.
		waitpid(fork_result, &term_information, 0);
	
		// Use WIFEXITED and / or WIFSIGNALED to check why
		// the child process terminated
		if (WIFEXITED(term_information)) {
			// This means the child process terminated by
			// exiting (so it returned from main, or it called
			// exit())

			// Now we can extract its exit status with
			// WEXITSTATUS
			int exit_status = WEXITSTATUS(term_information);
			printf("%d\n", exit_status);
		} else if (WIFSIGNALED(term_information)) {
			// This means the child process was terminated by
			// a POSIX signal that it did not handle

			// Now we can extract the signal number of the signal
			// that killed it using WTERMSIG
			int signal_number = WTERMSIG(term_information);
			printf("%d\n", signal_number);
		}

		// When you call waitpid(), instead of passing the PID of
		// a specific child process as the first argument, you can
		// instead pass -1.
		// pid_t pid_of_terminated_child = waitpid(-1, &term_information, 0);

		// This tells the parent process to wait until ONE of its
		// child processes has terminated. It will clean up that child
		// process, harvest its termination information, and RETURNS
		// the PID of that terminated child process.

		// You can also pass -N for the first argument to waitpid(),
		// where N >= 2. In that case, it waits until ONE of its child
		// processes with PGID=N has terminated. Cleans up that child,
		// harvests its termination information, and returns the PID
		// of the terminated child.

		// For the options argument to waitpid(), you can pass some
		// options. In particular, there's an option flag
		// called WNOHANG that's very useful. If you pass it as the
		// third argument to waitpid(), then waitpid() will not actually
		// wait. Instead of waiting, it checks WHETHER a specified
		// child process has terminated. In such a case, it cleans
		// it up, harvests its termination information, and returns
		// the PID of the terminated child. But if no such child process
		// has terminated, then it returns 0.
		
		// There's another function called wait().

	} else {
		// I am the parent, but fork() failed, so no child process
		// was created.
		
	}

	printf("%d\n", x); // Child and parent have separate copies of x.
			   // This prints 6 in the child, but 5 in the parent.

	printf("Hello, World!\n");
	printf("Goodbye, World!\n");

	// Some other process-related tools:
	//   1. getpid(). This returns the PID of the calling process.
	//   2. exit(). Terminates the calling process with the specified
	//   	exit status.
	//   3. atexit(): registers cleanup functions to be called at process
	//   	exit.
	
	// Fork bomb: A problem that occurs when a process forks many,
	// many children very quickly, uncontrolled. An explosion of processes
	// on the system, starves the entire system of resources.
	// If you do this on the ENGR servers, they will crash.
	// If you do this on the OS1 server, it will crash.
	//
	// For example:
	/*
	while(1) {
		pid_t fork_result = fork();
		printf("%d\n", fork_result);
	}
	*/

	// If you forkbomb the OS1 server, I'll scold you.
	//
	// If you forkbomb the flip servers (or any other non-OS1 ENGR
	// server), you'll be severely penalized.
}
