#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pathnode {
	char *path;
	struct _pathnode *next;

} pathnode;

char *_getenv(const char *name);

int main()
{
	char *path;
	char *item;
	pathnode *first, *current, *next;

	path = _getenv("PATH");
	item = strtok(path, "=");
	item = strtok(NULL, ":");

	first = malloc(sizeof(pathnode));
	current = first;

	while (item != NULL)
	{
		next = malloc(sizeof(pathnode));
		current->path = strdup(item);
		current->next = next;
		current = next;
		current->path = NULL;
		current->next = NULL;
		item = strtok(NULL, ":");
	}

	current = first;
	while (current != NULL && current->path != NULL)
	{
		printf("search path : %s\n", current->path);
		current = current->next;
	}

	next = first;
	while (next != NULL)
	{
		current = next;
		next = current->next;
		free(current->path);
		free(current);
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
