#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_ARGS 128
#define PATH_PREFIX "/bin/"

extern char **environ;

/**
 * count_tokens - Counts the number of tokens in a string.
 * @inputline: The input string.
 * @delims: The delimiter characters.
 *
 * Return: The number of tokens.
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
 * Return: An array of tokens.
 */
char **create_tok_array(char *inputline, char *delims, int toklen)
{
	char **token, **array;

	array = malloc(sizeof(char *) * (toklen + 1)); /* +1 for NULL */
	if (array == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = array;
	*token = strtok(inputline, delims);
	while (*token != NULL)
	{
		token++;
		*token = strtok(NULL, delims);
	}
	*token = NULL; /* Null terminate the array */
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
	char *cmdpath;
	int cmdlen = strlen(cmdname);

	cmdpath = malloc(sizeof(char) * (cmdlen + strlen(PATH_PREFIX) + 1));
	if (cmdpath == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	strcpy(cmdpath, PATH_PREFIX);
	strcat(cmdpath, cmdname);
	return (cmdpath);
}

/**
 * print_env - Prints the environment variables.
 */
void print_env(void)
{
	char **env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * run_cmd - Placeholder for future command execution logic.
 * @usr_input: An array of strings representing the command and arguments.
 *
 * Return: The exit status of the command.
 */
int run_cmd(char **usr_input)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *cmdpath = get_path(usr_input[0]);

		if (execve(cmdpath, usr_input, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	return (0);
}

/**
 * main - Simple shell implementation
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	char *inputline = NULL;
	size_t n = 0;
	ssize_t read;
	char **token_array = NULL;
	struct stat file_stat;
	int status;
	int toklen;

	printf("--------\n");
	printf("Welcome to Atlas Simple Shell!\n");
	printf("--------\n");

	while (1)
	{
		printf("$$ ");
		read = getline(&inputline, &n, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		inputline[strcspn(inputline, "\n")] = 0;
		toklen = count_tokens(inputline, " \t\n");
		token_array = create_tok_array(inputline, " \t\n", toklen);

		/* Handle empty input or "exit" command */
		if (token_array[0] == NULL || strcmp(token_array[0], "exit") == 0)
		{
			break;
		}
		else if (!strcmp(token_array[0], "env"))
		{
			print_env();
		}
		else
		{
			status = run_cmd(token_array);
		}

		free(token_array);
	}

	free(inputline);
	return (EXIT_SUCCESS);
}
