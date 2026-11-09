#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	close(1);
	int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
	printf("Hello, World!\n");
	fprintf(stderr, "FD: %d\n", fd);
}
