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
	char *delims = " \t\n", *cmdpath, *inputline = NULL, **token_array;
	int linelen = 0, toklen, status = 0;
	size_t n;

	if (argc > 1)
	{	/* non-interactive mode (run once, exit) */
		cmdpath = get_path(argv[1]);
		status = run_cmd(cmdpath, &argv[1]);
		free(cmdpath);
	}
	else
	{	/* interactive mode */
		if (isatty(STDIN_FILENO))/* if in user interactive mode */
			printf("--------\nWelcome to $$hell!\nGo away\n--------\n");
		do { /* loop indefinitely */
			if (isatty(STDIN_FILENO))
				printf("(ง'̀-'́)ง "); /* shell with an attitude */
			linelen = getline(&inputline, &n, stdin);/* get and measure input */
			toklen = count_tokens(inputline, delims);
			if (linelen > 1 && toklen > 0) /* is input valid ? */
			{	/* construct token array and get command path */
				token_array = create_tok_array(inputline, delims, ++toklen);
				cmdpath = get_path(*token_array);
				if (!strcmp(*token_array, "exit")) /* is the command exit ? */
				{
					free(cmdpath);
					free(token_array);
					break;
				}
				status = run_cmd(cmdpath, token_array); /* attempt execute command */
				free(cmdpath);
				free(token_array);
			}
		} while (linelen > -1);
	}
	free(inputline);
	return (status);
}
