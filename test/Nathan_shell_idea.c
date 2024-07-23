#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_ARGS 128
#define PATH_PREFIX "/bin/"

/**
 * main - Simple shell implementation
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	char *line = NULL, *token;
	size_t n = 0;
	ssize_t read;
	char *args[MAX_ARGS];
	struct stat st;
	int status;
	extern char **environ;

	printf("--------\n");
	printf("you have entered our\n\nAtlas\n Simple\n  Shell.\n\n");
	printf("go away\n");
	printf("--------\n");

	while (1)
	{
		printf("$$$hell :: ");
		read = getline(&line, &n, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		line[strcspn(line, "\n")] = 0;

		/* Tokenize command and arguments */
		int i = 0;
		args[i] = strtok(line, " \t\n");
		while (args[i] != NULL && i < MAX_ARGS - 1)
		{
			i++;
			args[i] = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		/* Exit on "exit" command */
		if (args[0] && strcmp(args[0], "exit") == 0)
		{
			break;
		}

		/* Check if command exists */
		char cmdpath[strlen(PATH_PREFIX) + strlen(args[0]) + 1];
		sprintf(cmdpath, "%s%s", PATH_PREFIX, args[0]);
		if (stat(cmdpath, &st) != 0)
		{
			perror(args[0]);
			continue;
		}

		/* Fork and execute command */
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{ /* Child process */
			execve(cmdpath, args, environ);
			perror("execve"); /* execve only returns on error */
			exit(1);		  /* Exit with an error status */
		}
		else
		{ /* Parent process */
			wait(NULL);
		}
	}

	free(line);
	return (EXIT_SUCCESS);
}
