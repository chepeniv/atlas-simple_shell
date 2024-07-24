#include "main.h"

#define MAX_ARGS 128
#define PATH_PREFIX "/bin/"

extern char **environ;

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
	*token = NULL;
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
	char **env = environ;
	char *path_value = NULL;
	char *path;
	char *dir;
	char *cmdpath;
	struct stat file_stat;

	while (*env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path_value = *env + 5;
			break;
		}
		env++;
	}

	if (!path_value)
	{
		return (NULL);
	}

	path = strdup(path_value);

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		cmdpath = malloc(strlen(dir) + strlen(cmdname) + 2);
		sprintf(cmdpath, "%s/%s", dir, cmdname);
		cmdpath[strlen(dir) + strlen(cmdname) + 1] = '\0';

		if (stat(cmdpath, &file_stat) == 0)
		{
			free(path);
			return (cmdpath);
		}
		free(cmdpath);
		dir = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
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
	int i;

	if (stat(cmdpath, &file_stat) == 0)
	{
		child_proc = fork();
		if (child_proc < 0)
		{
			perror("fork");
			return 1;
		}
		else if (child_proc == 0)
		{

			args = malloc(sizeof(char *) * (MAX_ARGS + 1));
			if (!args)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}

			args[0] = cmdpath; /* First argument is the command itself */
			for (i = 1; token_array[i - 1] != NULL && i < MAX_ARGS; i++)
			{
				args[i] = token_array[i - 1];
			}
			args[i] = NULL;

			if (execve(cmdpath, args, NULL) == -1)
			{
				perror(token_array[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", token_array[0]);
		return 1;
	}
	free(args);
	return 0;
}

/**
 * main - Simple shell implementation
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	char *inputline = NULL, **token_array = NULL;
	size_t n = 0;
	ssize_t read;
	struct stat file_stat;
	int status, toklen;

	if (isatty(STDIN_FILENO))
	{
		printf("--------\n");
		printf("Welcome to Atlas Simple Shell!\n");
		printf("Go away\n");
		printf("--------\n");
	}

	while ((read = getline(&inputline, &n, stdin)) != -1)
	{
		if (read > 0 && inputline[read - 1] == '\n')
			inputline[read - 1] = '\0';

		toklen = count_tokens(inputline, " \t\n");
		token_array = create_tok_array(inputline, " \t\n", toklen);

		if (toklen == 1)
		{
			continue;

			if (token_array[0] == NULL || strcmp(token_array[0], "exit") == 0)
				break;
			else if (!strcmp(token_array[0], "env"))
				print_env();
			else
			{
				char *cmdpath = get_path(token_array[0]);
				if (stat(cmdpath, &file_stat) == 0)
				{
					status = run_cmd(cmdpath, token_array);
					if (status == -1)
						fprintf(stderr, "%s: command not found\n", token_array[0]);
				}
				else
					perror(token_array[0]);

				free(cmdpath);
			}

			free(token_array);
		}

		free(inputline);
		return (EXIT_SUCCESS);
	}
