#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*simplify program if possible */
int main()
{
	unsigned int i, len;
	size_t n;
	ssize_t status;
	char *line = NULL;
	char *linedup = NULL;
	char *word = NULL;
	char **input = NULL;
	char **next = NULL;

	do
	{
		printf("$ ");
		status = getline(&line, &n, stdin);

		/*count delimeted substrings*/
		len = 1;
		linedup = strdup(line);
		word = strtok(linedup, " \t\n");
		if (!strcmp(word, "exit"))
		{
			free(linedup);
			break;
		}
		while (word != NULL)
		{
			word = strtok(NULL, " \t\n");
			len++;
		}

		/*allocate mem for array*/
		/*construct array */
		input = malloc(sizeof(void *) * len);
		*input = strtok(line, " \t\n");
		next = input;
		while (*next != NULL)
		{
			next++;
			*next = strtok(NULL, " \t\n");
		}

		/*iterate through and output array elements */
		i = 0;
		while (i < len - 1)
		{
			printf("%d -- %s\n", i, *(input + i));
			i++;
		}

		/*free mem*/
		free(linedup);
		free(input);

	} while (status > -1);

	free(line);
	return (0);
}
