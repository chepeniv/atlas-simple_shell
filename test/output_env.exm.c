/* ENVIRONMENT - via main()
 * example 1
 */

#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	unsigned int i;

	i = 0;
	while (env[i])
	{
		printf("env[%d] : %s \n", i, env[i]);
		i++;
	}
	return (0);
}
