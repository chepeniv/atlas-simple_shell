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
	ssize_t bytes_read; /* Renamed from 'read' */
	char *inputline = NULL;
	char *delims = " \t\n";
	char *cmdname = NULL;
	char **token_array = NULL;
	char *cmdpath;
	int status = 0;
	int pipefd[2]; /* File descriptors for the pipe */

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
			token_array = create_tok_array(inputline, " \t\n", toklen);

			if (token_array == NULL)
			{
				perror("Error: ");
			}

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
				if (pipe(pipefd) == -1)
				{ /* Create a pipe */
					perror("pipe");
					exit(EXIT_FAILURE);
				}

				status = run_cmd(cmdpath, token_array);
				if (status == -1)
				{
					fprintf(stderr, "%s: command not found\n", token_array[0]);
				}

				/* Read output from child process */
				close(pipefd[1]);  /* Close write end of the pipe */
				char buffer[1024];
				int nbytes;
				while ((nbytes = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
				{
					buffer[nbytes] = '\0';
					write(STDOUT_FILENO, buffer, nbytes);
				}
				close(pipefd[0]); /* Close read end of the pipe */
				free(cmdpath);
			}
			else
			{
				fprintf(stderr, "%s: command not found\n", token_array[0]);
			}

			free(token_array);
		} while (status != -1); /* Continue until an error occurs */
	}

	free(inputline);
	return (0);
}
