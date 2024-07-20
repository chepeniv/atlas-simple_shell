/* CREATING PROCESSES
 * example 1
 */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t this_proc, child_proc;

	printf("before forking\n");

	child_proc = fork();
	if (child_proc < 0)
	{
		perror("ERROR:");
		return (1);
	}

	this_proc = getpid();
	printf("code following a fork will be duplicated and executed by both the caller and its spawn : %u\n", this_proc);

	return (0);
}
