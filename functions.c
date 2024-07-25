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
	char **array = malloc(sizeof(char *) * (toklen + 1));
	char *token = strtok(inputline, delims);
	int i = 0;

	if (!array)
		return (NULL);

	while (token != NULL)
	{
		array[i++] = token;
		token = strtok(NULL, delims);
	}
	array[i] = NULL;
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

	/* Find the PATH environment variable */
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path_value = *env + 5; /* Skip "PATH=" */
			break;
		}
	}

	if (!path_value)
		return NULL; /* PATH not found */

	/* Duplicate the PATH value to tokenize */
	path = strdup(path_value);
	if (!path)
		return NULL;

	/* Tokenize the PATH variable */
	dir = strtok(path, ":");
	while (dir != NULL)
	{
		/* Allocate memory for the full command path */
		cmdpath = malloc(strlen(dir) + strlen(cmdname) + 2); /* +2 for '/' and '\0' */
		if (!cmdpath)
		{
			free(path);
			return NULL;
		}

		/* Construct the full command path */
		sprintf(cmdpath, "%s/%s", dir, cmdname);

		/* Check if the file exists and is executable */
		if (stat(cmdpath, &file_stat) == 0 && (file_stat.st_mode & S_IXUSR))
		{
			free(path);
			return cmdpath; /* Return the full command path if found */
		}

		free(cmdpath);
		dir = strtok(NULL, ":");
	}

	free(path);
	return NULL; /* Command not found in PATH */
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
		child_proc = fork(); /* Create a child process */
		if (child_proc < 0)
		{ /* Error handling for fork */
			perror("fork");
			return 1;
		}
		else if (child_proc == 0)
		{ /* Child process execution */
			/* Allocate memory for arguments array */
			args = malloc(sizeof(char *) * (MAX_ARGS + 1));
			if (!args)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}

			/* Construct arguments array for execve */
			arg_index = 0;
			while (token_array[arg_index] != NULL && arg_index < MAX_ARGS)
			{
				args[arg_index] = token_array[arg_index];
				arg_index++;
			}
			args[arg_index] = NULL;

			/* Execute command */
			execve(cmdpath, args, NULL); /* Execute the command */

			/* execve failed if we reach this point */
			perror(token_array[0]); /* Handle execution error */
			exit(127);				/* Exit child process with error code 127 (command not found) */
		}
		else
		{
			wait(NULL); /* Parent waits for child to complete */
		}
		free(args);
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", token_array[0]);
		return 1; /* Indicate command not found error */
	}
	return 0; /* Command executed successfully */
}
