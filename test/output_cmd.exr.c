#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	size_t n;
	ssize_t status;
	char *input = NULL;

	do
	{
		printf("$ ");
		status = getline(&input, &n, stdin);
		printf("%s", input);
	} while (status > -1 && input != "exit\n");

	free(input);
	return (0);
}
