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
	int get_env;

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
		/* Read user input */
		while (1)
		{
			/* Display prompt in interactive mode */
			if (isatty(STDIN_FILENO))
			{
				printf("$$ ");
			}

			status = getline(&inputline, &n, stdin);
			if (status == -1)
			{
				break; /* Exit on error or EOF */
			}
			inputline[strcspn(inputline, "\n")] = 0; /* Remove trailing newline */

			/* Tokenize input */
			toklen = count_tokens(inputline, delims);
			token_array = create_tok_array(inputline, delims, toklen);

			if (!token_array || !token_array[0])
			{
				free(token_array);
				continue; /* Skip empty lines or errors */
			}

			cmdname = token_array[0];

			/* Handle 'exit' command */
			if (!strncmp(cmdname, "exit", 4))
			{
				free(token_array);
				break;
			}
			else if (!strncmp(cmdname, "env", 3))
			{
				print_env();
			}
			else
			{
				cmdpath = get_path(cmdname);
				if (cmdpath)
				{
					status = run_cmd(cmdpath, token_array);
					if (status == -1)
						fprintf(stderr, "%s: command not found\n", token_array[0]);
					free(cmdpath);
				}
				else
				{
					fprintf(stderr, "%s: command not found\n", token_array[0]);
					status = 1;
				}
			}
			free(token_array);
		}
	}

	free(inputline);
	return (status);
}
