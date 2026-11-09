#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void) {
	int fd = open("in.txt", O_RDONLY);

	char buffer[1];
	read(fd, buffer, 1);

	pid_t fork_result = fork();

	if (fork_result == 0) {
		// Child process
		
		// Does the child process's file descriptor table have
		// a descriptor for fd? Yes. The child process inherits
		// a copy of its parent's file descriptor table.

		// File descriptors are preserved on fork().

		char child_buffer[1];
		read(fd, child_buffer, 1);
		printf("%c\n", child_buffer[0]);

		// File descriptors are freed from the process's FD table
		// when they're closed.
		close(fd);
		
		execlp("ls", "ls", NULL);

		// However, the file description that the pointer in the
		// row in the FD table points to, is freed the moment that
		// there are no  more file descriptors pointing to it in
		// all processes' file descriptor tables.
	} else {
		int termination_info;
		wait(&termination_info);
		
		char parent_buffer[1];
		read(fd, parent_buffer, 1);
		printf("%c\n", parent_buffer[0]);

		close(fd);
		// Parent process
	}
}
