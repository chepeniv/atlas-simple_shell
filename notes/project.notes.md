#BRIEF : 

##OBJECTIVES 
	- manipulating the environment of the current process
	- creating processes
	- the three prototypes of main
	- How does the shell use the PATH to find the programs
	- How to execute another program with the execve system call
	- How to suspend the execution of a process until one of its children terminates
	- What is a pid and a ppid

##REQUIREMENTS
	- Use system calls only when you need to
	- program must have the exact same output as sh (/bin/sh) as well as the exact same error output

##ALLOWED FUNCS AND SYSCALLS
	###man 2 (Syscalls):
	access, chdir, close, execve, _exit, fork, getpid, kill, open, read, signal, stat (\__xstat), lstat (\__lxstat), fstat (\__fxstat), wait, waitpid, wait3, wait4, write 

	###man 3 (libcalls):
	closedir, exit, fflush, free, getcwd, getline, isatty, malloc, strtok, readdir, opendir, perror, printf, fprintf, vfprintf, sprintf, putchar 

##COMPILATION :
	`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -ggdb3 *.c -o hsh`
