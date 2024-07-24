#include "main.h"

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
	int cmdlen;
	char *cmdpath;

	cmdlen = strlen(cmdname);

	cmdpath = malloc(sizeof(char) * (cmdlen + 6));
	cmdpath = strcpy(cmdpath, "/bin/");
	cmdpath = strcat(cmdpath, cmdname);

	return (cmdpath);
}

int run_cmd(char *cmdpath, char **token_array)
{
	struct stat file_stat;
	pid_t child_proc;
	char **args = NULL;
	int i, devNull;

	if (stat(cmdpath, &file_stat) == 0 && (file_stat.st_mode & S_IXUSR))
	{
		child_proc = fork();
		if (child_proc < 0)
		{
			perror("ERROR:");
			return (1);
		}
		else if (child_proc == 0)
		{

			/* Create args array with cmdpath as first element */
			args = malloc(sizeof(char *) * (MAX_ARGS + 1));
			if (!args)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			args[0] = cmdpath;
			for (i = 1; token_array[i - 1] != NULL && i < MAX_ARGS; i++)
			{
				args[i] = token_array[i - 1];
			}
			args[i] = NULL;

			/* Redirect standard input (stdin) to /dev/null */
			devNull = open("/dev/null", O_RDONLY);
			if (devNull == -1)
			{
				perror("open");
				exit(1);
			}
			if (dup2(devNull, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
			close(devNull);

			if (execve(cmdpath, args, NULL) == -1)
			{
				perror("ERROR:");
				exit(1); /* Exit the child process on error */
			}
		}
		else
		{

			wait(NULL);
		}
		free(args);
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", token_array[0]);
		return (1);
	}
	return (0);
}
