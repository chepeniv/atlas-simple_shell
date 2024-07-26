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
	size_t n;
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;
	int status;

	if (argc > 1)
	{
		/* Non-interactive mode: Execute a single command from arguments */
		cmdname = argv[1];
		cmdpath = get_path(cmdname);
		token_array = &argv[1];
		run_cmd(cmdpath, token_array);
		free(cmdpath);

		return (0);
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

			/* Tokenize input line and get command name */
			toklen = count_tokens(inputline, delims);
			token_array = create_tok_array(inputline, delims, toklen);
			cmdname = *token_array;

			/* Exit if the 'exit' command is entered */
			if (!strncmp(cmdname, "exit", 4))
			{
				free(inputline); /* Free allocated memory for inputline */
				free(token_array);
				return (0);
			}

			/* Get full path of command and execute it */
			cmdpath = get_path(cmdname);
			if (cmdpath)
			{
				status = run_cmd(cmdpath, token_array);
				if (status == -1)
					fprintf(stderr, "%s: command not found\n", token_array[0]);
				free(cmdpath);
			}
			free(token_array);
		} while (status != -1); /* Continue until an error occurs */
	}

	free(inputline);
	return (0);
}
