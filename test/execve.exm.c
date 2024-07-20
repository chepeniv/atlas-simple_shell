/* EXECUTING A PROGRAM
 * example 1
 */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("before calling execve\n");

	if (execve(argv[0], argv, NULL) == -1)
		perror("ERROR:");

	printf("after calling execve\n");
	return (0);
}
