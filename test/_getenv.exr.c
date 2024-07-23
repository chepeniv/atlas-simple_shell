#include <stdio.h>
#include <string.h>

char *_getenv(const char *name);

int main(int count, char **args)
{
	int j = 1;
	char *item;

	while (args[j])
	{
		item = _getenv(args[j]);
		printf("%s\n", item);
		j++;
	}

	return (0);
}

char *_getenv(const char *name)
{
	extern char **environ;
	char *item;
	int i = 0;

	while (environ[i])
	{
		item = environ[i];
		item = strtok(item, "=");

		if (!strcmp(name, item))
			return (environ[i]);
		i++;
	}
	return ("ITEM NOT FOUND");
}
