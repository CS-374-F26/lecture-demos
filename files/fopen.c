#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void) {
	mode_t old_umask = umask(0022); // This changes only the process's umask

	// Hypothetically, to restore the old umask:
	// umask(old_umask);

	

	// fopen(), when creating new files,
	// will try to give permissions 0666
	// to the file. Then the umask applies.
	FILE* my_file = fopen("a.txt", "w");
	fprintf(my_file, "Hello, %d\n", 12);
	fprintf(my_file, "Goodbye, %d\n", 13);
	fclose(my_file);

	int result = chmod("a.txt", 0664);
	if (result) {
		// An error occurred
		// Handle it carefully
		printf("Uh oh!\n");
		return 1;
	}

	FILE* data_file = fopen("data.txt", "r");
	char* line = NULL;
	size_t buffer_size = 0;
	ssize_t line_length = getline(&line, &buffer_size, data_file);
	if (feof(data_file)) {
		// We reached the end of the file. handle that.
	} else {
		printf("%s\n", line);
		printf("%zu\n", buffer_size);
		printf("%zd\n", line_length);
	}
	free(line);
	fclose(data_file);
}
