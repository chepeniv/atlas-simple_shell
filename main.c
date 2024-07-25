#include "main.h"

/**
 * main - Entry point of the simple shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	unsigned int toklen;
	size_t n = 0;
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;
	int status = 0;

	if (argc > 1)
	{
		/* Non-interactive mode: Execute a single command from arguments */
		cmdname = argv[1];
		cmdpath = get_path(cmdname);
		if (!cmdpath)
		{
			fprintf(stderr, "%s: command not found\n", cmdname);
			return (1);
		}
		status = run_cmd(cmdpath, &argv[1]);
		free(cmdpath);
		return (status);
	}
	else
	{
		/* Interactive mode */
		if (isatty(STDIN_FILENO))
		{
			printf("--------\n");
			printf("Welcome to Atlas Simple Shell!\n");
			printf("Go away\n");
			printf("--------\n");
		}

		do
		{
			/* Display prompt and read input line */
			if (isatty(STDIN_FILENO))
			{
				printf("$$ ");
			}

			status = getline(&inputline, &n, stdin);
			if (status == -1)
			{
				free(inputline);
				break;
			}

			/* Tokenize input line and get command name */
			toklen = count_tokens(inputline, delims);
			token_array = create_tok_array(inputline, delims, toklen);
			if (!token_array)
			{
				perror("Error: ");
				free(inputline);
				continue;
			}

			cmdname = token_array[0];
			if (!cmdname)
			{
				free(token_array);
				continue;
			}

			/* Exit if the 'exit' command is entered */
			if (strcmp(cmdname, "exit") == 0)
			{
				free(inputline);
				free(token_array);
				return (0);
			}

			/* Get full path of command and execute it */
			cmdpath = get_path(cmdname);
			if (cmdpath)
			{
				status = run_cmd(cmdpath, token_array);
				free(cmdpath);
			}
			else
			{
				fprintf(stderr, "%s: command not found\n", token_array[0]);
			}

			free(token_array);
		} while (1);
	}

	free(inputline);
	return (0);
}
