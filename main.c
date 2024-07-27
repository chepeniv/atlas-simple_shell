#include "main.h"

int main(int argc, char **argv)
{
	int linelen, toklen;
	size_t n;
	/* ssize_t status; */
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;

	if (argc > 1) /* non-interactive mode */
	{
		cmdname = argv[1];
		cmdpath = get_path(cmdname);
		token_array = &argv[1];
		run_cmd(cmdpath, token_array);
		free(cmdpath);
		return (0);
	}
	else
	{
		if (isatty(STDIN_FILENO))
		{
			printf("--------\n");
			printf("Welcome to Atlas Simple Shell!\n");
			printf("Go away\n");
			printf("--------\n");
		}

		do
		{
			if (isatty(STDIN_FILENO))
				printf("$$ ");

			linelen = getline(&inputline, &n, stdin);
			toklen = count_tokens(inputline, delims);
			if (linelen > 1 && toklen > 0)
			{
				toklen++;
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
				free(cmdpath);
				free(token_array);
			}
		} while (linelen > -1);

		free(inputline);
		return (0);
	}
}
