/* FILE INFORMATION
 * example 1
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	unsigned int i;
	struct stat file_stat;

	if (argc < 2)
	{
		printf("usage: %s path to file ...\n", argv[0]);
		return (1);
	}

	i = 0;
	while (argv[i])
	{
		printf("given filepath %s: ", argv[i]);
		if (stat(argv[i], &file_stat) == 0)
			printf("FOUND\n");
		else
			printf("NOT FOUND\n");
		i++;
	}
	return (0);
}
