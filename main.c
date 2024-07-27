#include "main.h"

int main(int argc, char **argv)
{
	char *delims = " \t\n", *cmdpath, *inputline, **token_array;
	int status, linelen, toklen;
	size_t n;

	if (argc > 1) /* non-interactive mode */
	{
		cmdpath = get_path(argv[1]);
		run_cmd(cmdpath, &argv[1]);
		free(cmdpath);
	}
	else
	{
		if (isatty(STDIN_FILENO))
			printf("--------\nWelcome to $$hell!\nGo away\n--------\n");
		do {
			if (isatty(STDIN_FILENO))
				printf("(ง'̀-'́)ง "); /* shell with an attitude */
			linelen = getline(&inputline, &n, stdin);
			toklen = count_tokens(inputline, delims);
			if (linelen > 1 && toklen > 0)
			{
				token_array = create_tok_array(inputline, delims, ++toklen);
				cmdpath = get_path(*token_array);
				if (!strcmp(*token_array, "exit"))
				{
					free(cmdpath);
					free(token_array);
					break;
				}
				status = run_cmd(cmdpath, token_array);
				free(cmdpath);
				free(token_array);
			}
		} while (linelen > -1);
		free(inputline);
	}
	return (status);
}
