// fopen(), fclose(), getline(), fprintf() are from the C standard library

// open(), close(), read(), write() are a POSIX alternative
// generally, read() and write() MUST be called within
//    a loop.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	// O_RDONLY, O_WRONLY, O_CREAT
	// To open a file for writing:
	// int fd = open("data.txt", O_WRONLY | O_CREAT, 0644);
	
	// To open a file for reading:
	int fd = open("data.txt", O_RDONLY);
	if (fd == -1) {
		// An error occurred.
		printf("Uh oh!\n");
		return 1;
	}

	char buffer[1024] = {0};
	size_t total_bytes_read_so_far = 0;
	while (1) {
		ssize_t n_bytes_read = read(
			fd,
			buffer + total_bytes_read_so_far,
			1023 - total_bytes_read_so_far
		);

		if (n_bytes_read <= 0) {
			break;
		}
		
		total_bytes_read_so_far += n_bytes_read;
	}

	printf("%s\n", buffer);

	close(fd);
}
