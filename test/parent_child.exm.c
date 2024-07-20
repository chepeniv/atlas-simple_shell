/* CREATING PROCESSES
 * example 2
 * here we determine which is the parent, and which is the child
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

	if (child_proc == 0)
		printf("this is the child proc: %u\n", this_proc);
	else
		printf("this is NOT the child proc: %u\n", this_proc);

	return (0);
}
