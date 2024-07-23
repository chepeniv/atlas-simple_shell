#include <stdio.h>

int main(int count, char **args, char **env)
{
	extern char **environ;

	printf("environ : %p \n", &environ);
	printf("*environ : %p \n", *environ);
	printf("env : %p \n", &env);
	printf("*env : %p \n", *env);

	return (0);
}
