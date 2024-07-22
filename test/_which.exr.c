#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	struct stat file_stat;
	char *fullpath;
	int len;

	if (argc != 2)
	{
		printf("usage: %s [filename]\n", argv[0]);
		return (1);
	}

	len = strlen(argv[1]);
	fullpath = malloc(sizeof(char) * (len + 3));
	fullpath = strcpy(fullpath, "./");
	fullpath = strcat(fullpath, argv[1]);

	if (stat(fullpath, &file_stat) == 0)
		printf("file '%s' exist in the current directory\n", argv[1]);
	else
		printf("file '%s' does NOT exist in the current directory\n", argv[1]);

	free(fullpath);

	return (0);
}
