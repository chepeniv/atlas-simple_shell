#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int i;
	int *status;
	pid_t this_proc, child_proc;
	char *argv[] = {"/bin/ls", "./", NULL};

	for (i = 0; i < 5; i++)
	{
		child_proc = fork();
		if (child_proc < 0)
		{
			perror("ERROR:");
			return (1);
		}
		else if (child_proc == 0)
		{
			printf("---- %d ----\n", i);
			if (execve(argv[0], argv, NULL) == -1)
				perror("ERROR:");
			break;
		}
		else
			wait(status);
	}

	return (0);
}
