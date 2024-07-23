#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[MAX_ARGS];
	pid_t pid;
	int status;
	extern char **environ; /* Get the environment variables */

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		line[strcspn(line, "\n")] = '\0'; 

		/*Tokenize input into arguments*/ 
		int i = 0;
		args[i] = strtok(line, " \t\n");
		while (args[i] != NULL && i < MAX_ARGS - 1)
		{
			i++;
			args[i] = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		/* Handle "exit" */
		if (args[0] && strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{ /* Child process */
			if (execve(args[0], args, environ) == -1)
			{
				perror(args[0]);
				exit(127);
			}
		}
		else
		{
			wait(&status);
		}
	}
}

