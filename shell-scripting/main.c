#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("%d\n", argc);
	printf("%s\n", argv[1]);

	// The return value of main() is the process's exit status.
	// It's an integer that somehow encodes something about
	// the success or failure of the process.
	//
	// The only convention: 0 indicates success, other integers
	// indicate failure.
	return 0;
}
