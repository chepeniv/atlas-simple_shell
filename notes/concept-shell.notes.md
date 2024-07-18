# PID, PPID
- these are used to by other programs and functions to interact with and manipulate the process
`$ man 2 getpid`
```
#include <sys/types.h>
#include <unistd.h>
...
	pid_t apid = getpid ();
	printf("%u\n", apid);
...
```
- every process has a parent process that created it and that in-turn has its own pid
- you can get the pid of the current process's parent by calling `getppid()`
- get the current shell's pid `echo $$`

# ARGUMENTS

- `int main(int argc, char **argv)`
- `$ man 3 getline`

# EXECUTING A PROGRAM

- syscall `execve(const char *pathname, char *const argv[], char *const envp[])` allows a process to execute another program
	- `pathname` : pathname to the command to execute
	- `argv` : arguments to pass along
		- format : `{"var1=val1", "var2=val2", ..., NULL}`
	- `envp` : environment variables list
		- `argv` and `envp` are arrays of pointers to strings
- this syscall loads the new program inplace of its caller in the stack (?)
- upon success, execve does not return to continue the rest of it's calling func
- THIS SYSCALL DISCARDS THE CALLING PROC
- `execve` only returns if there is a problem

# CREATING PROCESSES

- syscall `pid_t fork(void)` creates a new child proc nearly identical to it's caller
- when fork returns, the two process will run simultaneosly on different stacks, data, and heaps within the same program
- with `fork`'s return value it can be determined if the current proc is the parent or the child 
	- returns `0` to the child, and the child's pid to the parent

# WAIT

- the syscall `pid_t wait(int *status)` suspends execution of the caller until one of its children terminates

# FILE INFORMATION

- the syscall `int stat(char *pathname, struct stat *statbuf)` gets the status of a file
	- success, 0; error, -1

# ENVIRONMENT

- the shell uses an environment list wherein environment variables are stored
- a list is an array of strings with the format "var=value"
- `$ printenv`
- every proc comes with it's own environment
	- child processes inherit the a copy of their parent's env
- access the entire environment within a proc via `main()` or with the global variable `environ` 

## main()

- `int main(int agrc, char **argv, char **env)` (env is a NULL terminated array of strings)
- all the environment variables would be stored within `env`

# ADENDUM

context switch
: wherein a system saves the current state of processing of a cpu (unloading) before recontextualising (loading) it with new data for some other process

