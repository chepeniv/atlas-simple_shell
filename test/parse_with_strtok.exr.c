#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	size_t n;
	ssize_t status;
	char *input = NULL;
	char *word = NULL;

	do
	{
		printf("$ ");
		status = getline(&input, &n, stdin);
		word = strtok(input, " \t\n");

		if (!strcmp(word, "exit"))
			return (0);

		while (word != NULL)
		{
			printf("%s|", word);
			word = strtok(NULL, " \t\n");
		}
		printf("\n");
	} while (status > -1);

	free(input);
	free(word);
	return (0);
}
