#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	pid_t pid = strtol(argv[1], NULL, 10);

	kill(pid, SIGTERM);
}
