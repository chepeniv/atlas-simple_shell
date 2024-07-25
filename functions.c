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
	char *path_value = NULL, *path = NULL, *dir = NULL, *cmdpath = NULL;
	struct stat file_stat;
	int found_path = 0;

	/* Iterate over environment variables until we find the PATH variable */
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path_value = *env + 5; /* Skip "PATH=" */
			break;
		}
	}

	if (path_value == NULL)
	{
		return NULL;
	}

	path = strdup(path_value);
	dir = strtok(path, ":");

	while (dir != NULL)
	{
		cmdpath = malloc(strlen(dir) + strlen(cmdname) + 2); /* +2 for '/' and '\0' */
		sprintf(cmdpath, "%s/%s", dir, cmdname);
		cmdpath[strlen(dir) + strlen(cmdname) + 1] = '\0'; /* Ensure null-termination */

		if (stat(cmdpath, &file_stat) == 0 && (file_stat.st_mode & S_IXUSR))
		{
			found_path = 1;
			break; /* Found the command, exit the loop */
		}

		free(cmdpath);
		dir = strtok(NULL, ":");
	}

	free(path);

	if (found_path)
	{
		return cmdpath; /* Return the full command path if found */
	}
	else
	{
		return NULL; /* Command not found in PATH */
	}
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
	int arg_index = 0;

	if (stat(cmdpath, &file_stat) == 0 && (file_stat.st_mode & S_IXUSR))
	{
		child_proc = fork();
		if (child_proc < 0)
		{
			perror("fork");
			return 1;
		}
		else if (child_proc == 0)
		{

			/* argument array creation */
			args = malloc(sizeof(char *) * (MAX_ARGS + 1));
			if (!args)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}

			/* Build the args array correctly */
			arg_index = 0;
			while (token_array[arg_index] != NULL && arg_index < MAX_ARGS)
			{
				args[arg_index] = token_array[arg_index];
				arg_index++;
			}
			args[arg_index] = NULL; /* Null-terminate the args array */

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
		return (1); /* Indicate command not found error */
	}
	return (0); /* Command executed successfully */
}