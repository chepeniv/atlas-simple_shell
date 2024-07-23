#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*simplify program if possible */
int main()
{
	unsigned int i, len;
	size_t n;
	ssize_t status;
	char *line = NULL;
	char *delims = " \t\n";
	char *linedup = NULL;
	char *word = NULL;
	char **input = NULL;
	char **next = NULL;
	int *forkstatus;
	pid_t this_proc, child_proc;
	struct stat file_stat;
	char *cmdpath;
	int cmdlen;

	printf("--------\n");
	printf("you have entered our\n\nAtlas\n Simple\n  Shell.\n\n");
	printf("welcome\n");
	printf("--------\n");
	do
	{
		printf("$$$hell :: ");
		status = getline(&line, &n, stdin);

		linedup = strdup(line);
		word = strtok(linedup, delims);

		/*exit shell*/
		if (!strcmp(word, "exit"))
		{
			free(linedup);
			printf("exiting...\n");
			break;
		}

		/*count delimeted substrings*/
		len = 1;
		while (word != NULL)
		{
			word = strtok(NULL, delims);
			len++;
		}

		/*allocate mem and construct array */
		input = malloc(sizeof(void *) * len);
		*input = strtok(line, delims);
		next = input;
		while (*next != NULL)
		{
			next++;
			*next = strtok(NULL, delims);
		}

		/*construct cmdpath*/
		cmdlen = strlen(*input);
		cmdpath = malloc(sizeof(char) * (cmdlen + 6));
		cmdpath = strcpy(cmdpath, "/bin/");
		cmdpath = strcat(cmdpath, *input);

		/*create subproc and exec command given*/
		if (stat(cmdpath, &file_stat) == 0)
		{
			child_proc = fork();
			if (child_proc < 0)
			{
				perror("ERROR:");
				return (1);
			}
			else if (child_proc == 0)
			{
				if (execve(cmdpath, input, NULL) == -1)
					perror("ERROR:");
				break;
			}
			else
				wait(forkstatus);
		}

		/*free mem*/
		free(cmdpath);
		free(linedup);
		free(input);

	} while (status > -1);

	free(line);
	return (0);
}
