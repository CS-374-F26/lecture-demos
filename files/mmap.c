// Memory in a system is divided into chunks called pages.
// On x86_64 Linux, a page is 4 KB.

// Every process has what's known as a virtual address space.
// This is part of a technique called virtualization.

// Maps memory addresses in process to memory addresses in
// RAM.

// Suppose you have two processes, A and B.
// In process A, memory address 0x0005 might correspond to (map to)
// physical memory address 1000000. Whereas in process B, the
// same memory address 0x0005 might correspond to physical memory
// address 2000000.

// mmap() is a function in C that lets you map a chunk of contents
// of a file into your process's virtual address space (in memory).
// Basically, it lets you set up a big byte array through which
// you can access the file's contents.

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main(void) {
	int fd = open("data.txt", O_RDONLY);
	
	char* mapped_memory = mmap(NULL, 30, PROT_READ, MAP_SHARED, fd, 0);

	// If you want to expand / shrink the file's allocated size on disk,
	// for purposes of modifications via mmap'd memory region
	// (e.g., with O_WRONLY and PROT_WRITE and MAP_SHARED),
	// then you have to use tools like fallocate() to do that reallocation.

	for (size_t i = 0; i < 27; ++i) {
		printf("%c", mapped_memory[i]);
	}

	printf("\n");

	munmap(mapped_memory, 27);
	close(fd);
}
