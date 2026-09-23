#include <stdio.h>
#include <stdlib.h>

// Data segment
// 	read-only section
// 	read/write section
// Stack
// Heap

// Every function call gets a stack frame that's just big enough
// to store all of its locals. The stack is managed automatically.
// (automatic storage duration). Efficient. Easy to use.
//
// The heap haves dynamic storage duration.
int main(void) {
	// C does allow VLAs (as of C99)
	// Changing the size of an array / string / whatever is REALLY hard
	// to do on the stack.

	// Allocate on the heap:
	// malloc()
	// realloc()
	// calloc()
	int* numbers = malloc(sizeof(int) * 12);
	numbers[0] = 12;
	printf("%d\n", numbers[0]);

	// A memory leak is when you allocate memory on the heap but forget
	// to free it.

	// Delete from the heap:
	// free()
	
	// To expand our array and make it size 13
	numbers = realloc(numbers, sizeof(int) * 13);
	numbers[12] = 100;

	// Rules on freeing dynamic memory:
	// 1. Remember to do it
	// 2. But don't do it too early
	// 3. Don't do it more than once
	free(numbers);
	// free(numbers); // Double free
	
	// Free your dynamic memory when you're certain you're completely done
	// with it. Whenever your last stack-allocated pointer pointing to
	// the heap-allocated data is about to fall out of scope, that's a
	// good time to free the heap-allocated data.
	
	
}
