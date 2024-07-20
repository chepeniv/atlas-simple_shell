/* PID, PPID
 * example 1
 */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t this_proc, parent_proc;

	this_proc = getpid();
	parent_proc = getppid();

	printf("this currently running proc was assigned the id : %u\n", this_proc);
	printf("the parent caller of this proc has the id : %u\n", parent_proc);

	return (0);
}
