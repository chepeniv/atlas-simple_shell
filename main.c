#include "main.h"

int main(int argc, char **argv)
{
	int status, linelen, toklen;
	size_t n;
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
			printf("--------\nWelcome to $$hell!\nGo away\n--------\n");
		do
		{
			if (isatty(STDIN_FILENO))
				printf("(ง'̀-'́)ง "); /* shell with an attitude */

			linelen = getline(&inputline, &n, stdin);
			toklen = count_tokens(inputline, delims);
			if (linelen > 1 && toklen > 0)
			{
				token_array = create_tok_array(inputline, delims, ++toklen);
				cmdname = *token_array;
				cmdpath = get_path(cmdname);

				if (!strcmp(cmdname, "exit"))
				{
					free(cmdpath);
					free(token_array);
					break;
				}

				status = run_cmd(cmdpath, token_array);
				free(cmdpath);
				free(token_array);
			}
		} while (status == 0);

		free(inputline);
		return (0);
	}
}
