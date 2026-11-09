#include <unistd.h>
#include <stdio.h>

int main(void) {
	int pipe_fds[2];
	pipe(pipe_fds);

	int pipe2_fds[2];
	pipe(pipe2_fds);

	pid_t fork_result = fork();
	
	if (fork_result == 0) {
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		// Child process.
		// If you write into a pipe, but all FDs for the reading
		// end (across all processes) have been closed, and therefore
		// the reading file DESCRIPTION has been closed, then the
		// write() call will fail and raise SIGPIPE. By default,
		// this will kill the writing process (unless SIGPIPE is caught
		// or ignored).
		write(pipe_fds[1], "A", 1);

		char buffer[1];
		read(pipe2_fds[0], buffer, 1);
		printf("%c\n", buffer[0]);

		close(pipe_fds[1]);
		close(pipe2_fds[0]);
	} else {
		close(pipe_fds[1]);
		close(pipe2_fds[0]);
		// Parent process. 
		// char buffer[1];
		// read(pipe_fds[0], buffer, 1);
		// printf("%c\n", buffer[0]);

		write(pipe2_fds[1], "A", 1);

		close(pipe_fds[0]);
		close(pipe2_fds[1]);

	}

	// Pipes are an IPC mechanism (interprocess communication).
}
