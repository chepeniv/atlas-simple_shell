#include "main.h"

int count_tokens(char *input, char *delims);
char **create_tok_array(char *input, char *delims, int toklen);
char *get_path(char *cmdname);
int run_cmd(char *cmdpath, char **usr_input);

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
	}
	return (0);
}

