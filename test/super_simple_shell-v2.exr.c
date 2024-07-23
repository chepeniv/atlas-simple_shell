#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int count_tokens(char *input, char *delims);
char **create_tok_array(char *input, char *delims, int toklen);
char *get_path(char *cmdname);
int run_cmd(char *cmdpath, char **usr_input);

/*simplify program if possible */
int main()
{
	unsigned int i, toklen;
	size_t n;
	ssize_t status;
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;
	int cmdlen;

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
	int cmdlen;
	char *cmdpath;

	cmdlen = strlen(cmdname);

	cmdpath = malloc(sizeof(char) * (cmdlen + 6));
	cmdpath = strcpy(cmdpath, "/bin/");
	cmdpath = strcat(cmdpath, cmdname);

	return(cmdpath);
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
			perror("ERROR:");
			return (1);
		}
		else if (child_proc == 0)
		{
			if (execve(cmdpath, token_array, NULL) == -1)
				perror("ERROR:");
			return (-1);
		}
		else
			wait(&child_proc);
	}
}

