#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	// What if you want to write a C program that reads the contents
	// of a directory?
	
	// To do this, we must use directory streams.
	
	DIR* dstream = opendir("some_other_directory");
	int dstream_fd = dirfd(dstream);

	// Here, we can read the entries of the directory stream
	// one at a time with the readdir() function
	
	// readdir() reads the NEXT entry in the directory stream,
	// always picking up where it left off. The ordering of
	// the iterated entries is ambiguous.
	struct dirent* entry;

	while (entry = readdir(dstream)) {
		if (strcmp(entry->d_name, ".") == 0) {
			continue;
		}
		if (strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		struct stat statbuf;
		fstatat(dstream_fd, entry->d_name, &statbuf, 0);
		printf("%jd  ", (intmax_t) statbuf.st_size);
		// printf("%s  ", entry->d_name);
	}

	closedir(dstream);

	printf("\n");

	// readdir() always picks up where it left off.
	// What happens if the directory's contents are modified externally
	//    in the middle of a readir() loop? The behavior is unspecified.
	// readdir() does not return entries in any particular order. But
	// 	won't return duplicates.
	// readdir() WILL return . and .. entries, which you often need to
	// ignore (you will need to do this for assignment 2, else you'll
	// recurse into .., leading to infinite recursion).
}
