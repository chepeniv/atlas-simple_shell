#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Simple shell modification
 *
 * Return: 0 on success, 1 on error.
 */
int main(void)
{
	unsigned int i, len;
	size_t n;
	ssize_t status;
	char *line = NULL, *delims = " \t\n";
	char **input = NULL;
	int *forkstatus;
	pid_t child_pid;

	do
	{
		printf("$$$hell :: ");
		status = getline(&line, &n, stdin);

		if (status == -1)
			break; /* Handle EOF */

		/* Tokenize and count arguments */
		len = 0;
		input = malloc(sizeof(char *) * 1024); /* Assume max 1023 args */
		input[len] = strtok(line, delims);
		while (input[len] != NULL)
		{
			len++;
			input[len] = strtok(NULL, delims);
		}
		input[len] = NULL; /* Null terminate the array */

		/* Handle "exit" command */
		if (strcmp(input[0], "exit") == 0)
		{
			printf("exiting...\n");
			break;
		}

		/* Fork and execute command */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		else if (child_pid == 0)
		{
			if (execve(input[0], input, NULL) == -1)
			{
				perror("execve failed");
				exit(1); /* Child exits on uh-oh */
			}
		}
		else
		{
			wait(forkstatus); /* Parent waits for child to get outta daycare*/
		}

		free(input);

	} while (1); /* Foreva loop*/

	free(line);
	return (0);
}