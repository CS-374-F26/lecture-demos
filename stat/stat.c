// stat()-family functions.

// Suppose you want to retrieve information about a file.
// You have to stat() the file.

#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>

int main(void) {
	struct stat statbuf;
	// lstat() is identical to stat() except...
	//
	int stat_res = stat("hello-world.txt", &statbuf);
	if (stat_res) {
		// Error occurred. Handle it
		printf("Uh oh!\n");
		return 1;
	}

	// The size of hello-world.txt in bytes
	printf("%jd\n", (intmax_t) statbuf.st_size);

	if ((statbuf.st_mode & S_IFMT) == S_IFREG) {
		// hello-world.txt is a regular file
		printf("hello-world.txt is a regular file!\n");
	} else if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
		printf("hello-world.txt is a directory!\n");
	}

	// st_mode & 0000000000000001
	// st_mode & 0000000000000100
	if (statbuf.st_mode & 0100) {
		printf("hello-world.txt is executable by owning user\n");
	}

	if (statbuf.st_mode & 0040) {
		printf("hello-world.txt is readable by owning group\n");
	}


}
