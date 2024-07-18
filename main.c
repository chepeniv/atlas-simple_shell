#include "main.h"

int main(int argc, char **argv)
{
	char *input;

	input = malloc(sizeof(char) * 128);
	if (argc == 1)
	{
		printf("WELCOME TO THE ATLAS SHELL (ash)\n");
		do
		{
			printf(">> ");
			scanf("%s", input);
		} while (strcmp(input, "exit"));
		free(input);
		printf("GOODBYE!\n");
	}
	return (0);
}
