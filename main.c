#include "main.h"

int main(int argc, char **argv)
{
	unsigned int toklen;
	size_t n;
	ssize_t status;
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;

	if (argc > 1)
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
			free(cmdpath);
			free(token_array);

		} while (status > -1);

		free(inputline);
		return (0);
	}
}
