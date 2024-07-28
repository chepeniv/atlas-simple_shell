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
	int len = 0;
	char *linedup, *token;

	/*
	 * because strtok destroys the string it operates on
	 * we malloc-duplicate a dummy
	 */
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

		/* initialize the array */
		array = malloc(sizeof(void *) * toklen);
		*array = strtok(inputline, delims);

		/* add tokes to the array untill NULL is returned */
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
	int cmdlen;
	char *cmdpath;

	/*
	 * special cases where command given is either
	 * an absolute path or a relative path
	 */
	if (cmdname[0] == '/' || cmdname[0] == '.')
	{
		cmdpath = strdup(cmdname);
		return (cmdpath);
	}
	/* special env command given */
	else if (!strcmp(cmdname, "env"))
	{
		cmdpath = strdup(cmdname);
		return (cmdpath);
	}
	/* otherwise construct a fullpath for the command given */
	cmdlen = strlen(cmdname);
	cmdpath = malloc(sizeof(char) * (cmdlen + 6));
	cmdpath = strcpy(cmdpath, "/bin/");
	cmdpath = strcat(cmdpath, cmdname);

	return (cmdpath);
}

/**
 * run_cmd - Executes a command with arguments.
 * @cmdpath: The full path to the command.
 * @token_array: An array of strings containing arguements.
 *
 * Return: The exit status of the command.
 */
int run_cmd(char *cmdpath, char **token_array)
{
	struct stat file_stat;
	pid_t child_proc;

	/* execute _env() for special env command given */
	if (!strcmp(cmdpath, "env"))
		_env();
	/* otherwise ask operating system to run the command */
	else if (stat(cmdpath, &file_stat) == 0) /*executable exist */
	{
		child_proc = fork(); /*create subprocess*/
		if (child_proc < 0)
		{
			perror("ERROR: failed to fork()\n");
			return (errno);
		}
		else if (child_proc == 0)
		{	/* replace the subprocess with the exec program */
			if (execve(cmdpath, token_array, NULL) == -1)
				perror("ERROR: failed to create child proc\n");
			return (errno);
		}
		else /* parent process waits for the subprocess to conclude */
			wait(&child_proc);
	}
	return (errno);
}

/**
 * _env - get environment
 *
 * Return: environ duplicate
 */
char **_env(void)
{
	int i = 0;
	char **env;

	/* copy system's environ array onto our programs array */
	env = environ;
	while (env[i])
	{
		/* output the contents of array to stdout */
		printf("%s\n", env[i]);
		i++;
	}
	return (env);
}
