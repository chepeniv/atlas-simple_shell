/* WAIT
 * example 1
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int status;
	pid_t child_proc, this_proc;

	child_proc = fork();
	if (child_proc < 0)
	{
		perror("ERROR:");
		return (1);
	}

	this_proc = getpid();

	if (child_proc == 0)
	{
		printf("child proc : %u put on momentary pause\n", this_proc);
		sleep(8);
	}
	else
	{
		printf("parent proc waiting on the child proc return: \n");
		wait(&status);
		printf("the child proc returned with status : %d\n", status);
	}

	return (0);
}
