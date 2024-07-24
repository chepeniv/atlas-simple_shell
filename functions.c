#include "main.h"

/**
 * count_tokens - Counts the number of tokens in a string.
 * @inputline: The input string.
 * @delims: The delimiter characters.
 *
 * Return: The number of tokens in your coin cup.
 */
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

/**
 * create_tok_array - Creates an array of tokens from a string.
 * @inputline: The input string.
 * @delims: The delimiter characters.
 * @toklen: The number of tokens.
 *
 * Return: An array of tokens for arcade fun!
 */
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

/**
 * get_path - Gets the full path of a command.
 * @cmdname: The command name.
 *
 * Return: The full path of the command.
 */
char *get_path(char *cmdname)
{
	char **env;
	char *path_env = NULL;
	char *path = NULL;
	char *dir = NULL;
	char *cmdpath = NULL;
	struct stat file_stat;

	/* Find PATH from the environment variables */
	for (char **env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path_env = *env + 5; /* Skip "PATH=" */
			break;
		}
	}

	if (path_env == NULL)
	{
		return NULL;
	}

	path = strdup(path_env);
	dir = strtok(path, ":");

	while (dir != NULL)
	{
		cmdpath = malloc(strlen(dir) + strlen(cmdname) + 2); /* +2 for '/' and '\0' */
		sprintf(cmdpath, "%s/%s", dir, cmdname);
		cmdpath[strlen(dir) + strlen(cmdname) + 1] = '\0'; /* Ensure null-termination */

		if (stat(cmdpath, &file_stat) == 0 && (file_stat.st_mode & S_IXUSR))
		{
			free(path);
			return cmdpath;
		}

		free(cmdpath);
		dir = strtok(NULL, ":");
	}

	free(path);
	return NULL;
}

/**
 * run_cmd - Executes a command with arguments.
 * @cmdpath: The full path to the command.
 * @args: An array of strings containing arguements.
 *
 * Return: The exit status of the command.
 */
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
