#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include "main.h"

int count_tokens(char *input, char *delims);
char **create_tok_array(char *input, char *delims, int toklen);
char *get_path(char *cmdname);
int run_cmd(char *cmdpath, char **usr_input);

/*simplify program if possible */
int main()
{
	unsigned int toklen;
	size_t n;
	ssize_t status;
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;

	do
	{
		printf("$$ ");
		status = getline(&inputline, &n, stdin);

		toklen = count_tokens(inputline, delims);
		token_array = create_tok_array(inputline, delims, toklen);
		cmdname = *token_array;
		cmdpath = get_path(cmdname);

		if (!strcmp(cmdname, "exit"))
		{
			free(cmdpath);
			free(token_array);
			break;
		}

		run_cmd(cmdpath, token_array);

		/*free mem*/
		free(cmdpath);
		free(token_array);

	} while (status > -1);

	free(inputline);
	return (0);
}

int count_tokens(char *inputline, char *delims)
{
	int len = 1;
	char *linedup, *token;

	linedup = strdup(inputline);
	token = strtok(linedup, delims);
	while (token != NULL)
	{
		token = strtok(NULL, delims);
		len++;
	}
	free(linedup);

	return (len);
}

char **create_tok_array(char *inputline, char *delims, int toklen)
{
	char **token, **array;

	array = malloc(sizeof(void *) * toklen);
	*array = strtok(inputline, delims);

	token = array;
	while (*token != NULL)
	{
		token++;
		*token = strtok(NULL, delims);
	}
	return (array);
}

char *get_path(char *cmdname)
{
	int cmdlen = strlen(cmdname);
	char *cmdpath = malloc(cmdlen + 6);
	if (cmdname[0] == '/')
	{
		strcpy(cmdpath, cmdname);
	}
	else
	{
		snprintf(cmdpath, cmdlen + 6, "/bin/%s", cmdname);
	}
	return cmdpath;
}

int run_cmd(char *cmdpath, char **token_array)
{
	struct stat file_stat;
	int status;
	pid_t child_proc;
	char **args;

	if (stat(cmdpath, &file_stat) == -1)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "Command not found: %s\n", cmdpath);
			return 127;
		}
		else
		{
			perror("stat");
			return 1;
		}
	}

	child_proc = fork();
	if (child_proc == -1)
	{
		perror("fork");
		return 1;
	}
	else if (child_proc == 0)
	{
		args = malloc(3 * sizeof(char *));
		args[0] = token_array[0];
		args[1] = token_array[1];
		args[2] = NULL;

		execve(cmdpath, args, NULL);
		perror("execve");
		free(args);
		exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
		else
		{
			return 1;
		}
	}
}
