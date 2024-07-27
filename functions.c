#include "main.h"

int count_tokens(char *input, char *delims);
char **create_tok_array(char *input, char *delims, int toklen);
char *get_path(char *cmdname);
int run_cmd(char *cmdpath, char **usr_input);

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
	int cmdlen;
	char *cmdpath;

	if (cmdname[0] == '/' || cmdname[0] == '.')
	{
		cmdpath = strdup(cmdname);
		return (cmdpath);
	}
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

	if (stat(cmdpath, &file_stat) == 0)
	{
		child_proc = fork();
		if (child_proc < 0)
		{
			perror("ERROR: failed to fork()\n");
			return (-1);
		}
		else if (child_proc == 0)
		{
			if (execve(cmdpath, token_array, NULL) == -1)
				perror("ERROR: failed to create child proc\n");
			return (-1);
		}
		else
			wait(&child_proc);
		return (0);
	}
	else
		return (2);
}

