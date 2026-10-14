#include <stdio.h>

// Kernel threads in  memory:
// Every kernel thread gets its own stack. But they share all other memory.

void foo(float x, _Bool y) {
	// does nothing
	printf("%.2f\n", x);
}

int main(void) {
	// What is a function pointer?
	// A pointer to a function.
	//
	// Functions are stored in memory.
	//
	
	void (*my_pointer)(float, _Bool) = foo;

	my_pointer(3.14, 1);

	
}
