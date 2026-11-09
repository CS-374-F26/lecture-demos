#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	dup2(fd, STDOUT_FILENO);
	close(fd); // A good idea

	printf("Hello, World!\n");

	fprintf(stderr, "Goodbye, World!\n");

	/*
	int new_fd = dup(fd);

	write(fd, "a", 1);
	close(fd);
	
	write(new_fd, "b", 1);

	close(new_fd);
	*/
}
