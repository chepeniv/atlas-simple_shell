#include <stdio.h>

int main()
{
	int i = 0;
	extern char **environ;

	while (environ[i])
	{
		printf("item %d : %s\n", i, environ[i]);
		i++;
	}

	return (0);
}
