#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name);

int main()
{
	char *path;
	char *item;

	path = _getenv("PATH");
	item = strtok(path, "=");
	item = strtok(NULL, ":");

	while (item != NULL)
	{
		printf("%s\n", item);
		item = strtok(NULL, ":");
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
		item = strdup(item);
		item = strtok(item, "=");

		if (!strcmp(name, item))
		{
			free(item);
			return (environ[i]);
		}
		free(item);
		i++;
	}
	return (NULL);
}
