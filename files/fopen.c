#include <stdlib.h>
#include <stdio.h>

int main(void) {
	FILE* my_file = fopen("a.txt", "w");
	fprintf(my_file, "Hello, %d\n", 12);
	fprintf(my_file, "Goodbye, %d\n", 13);
	fclose(my_file);

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
