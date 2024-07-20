/* ENVIRONMENT - via main()
 * example 1
 */

#include <stdio.h>

int main(int argc, char **argv)
{
	while (*argv)
	{
		printf("*argv != NULL : %s\n", *argv);
		argv++;
	}
	return (0);
}
