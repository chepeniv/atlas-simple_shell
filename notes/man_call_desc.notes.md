# System Calls (man 2)

## `int access(const char *pathname, int mode)`
	- `#include <unistd.h>`
		- checks whether the calling process can access the file pathname
		- `mode` specifies the accessibility checks to perform
	- return : success [0] ; failure [-1]

## `int chdir(const char *path)`
	- `#include <unistd.h>`
	- changes the working directory of the calling process to the specified one
	- return : success [0] ; failure [-1]

## `int close(int fdesc)`
	- `#include <unistd.h>`
	- closes a file descriptor, so that it no longer refers to any file and may be reused
	- return : success [0] ; failure [-1]

## `int execve(const char *path, char *const argv[], char *const envp[])`
	- `#include <unistd.h>`
	- executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be replaced with a new program
	- return : success [DOES NOT RETURN] ; failure [-1]

## `void _exit(int status)`
	- `#include <unistd.h>`
	- terminates the calling process "immediately"
		- any open file descriptors belonging to the process are closed
		- any children of the process are inherited by init(1)
		- `status` is returned the parent and collected by `wait()`
	- return : [DOES NOT RETURN] 

## `pid_t fork(void)`
	- `#include <unistd.h>`
	- `#include <sys/types.h>`
	- creates a new process by duplicating the calling process
		- run in separate memory spaces
	- return : success [child pid (to the parent)], [0 (to the child)] ; failure [-1] to the parent and no subproc is created to the parent and no subproc is created

## `pid_t getpid(void)`
## `pid_t getppid(void)`
	- `#include <unistd.h>`
	- `#include <sys/types.h>`
	- `getpid` returns the process ID (PID) of the calling process
	- `getppid` returns the process ID (PID) of the parent process

## `int kill(pid_t pid, int sig)`
	- `#include <signal.h>`
	- `#include <sys/types.h>`
	- used to send any signal to any process group or process
		- positive pid - signal sig is sent to the process with the ID specified
		- pid = 0 - sig is sent to every process in the process group of the calling process
		- pid = -1 - sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init)
		- pid < -1 - sig is sent to every process in the process group whose ID is -pid
	- If sig is 0, then no signal is sent, but existence and permission checks are still performed
	- return : success (at least one signal was sent) [0] ; failure [-1]

## `int open(const char *path, int flags)`
## `int open(const char *path, int flags, mode_t mode)`
	- `#include <sys/types.h>`
	- `#include <sys/stat.h>`
	- `#include <fcntl.h>`
	- open and possibly create a file specified by path
	- return : success [file descriptor], failure [-1]

## `ssize_t read(int fd, void *buf, size_t lenth)`
	- `#include <unistd.h>`
	- attempts to read up to length bytes from file descriptor into the buffer 
	- return : success [number of bytes], failure [-1]

## `sighandler_t signal(int signum, sighandler_t handler)`
	- `#include <signal.h>`
	- `typedef void (*sighandler_t)(int)`
	- sets the "disposition" of the signal signum to handler
	- __it sets what the signal does to whatever the handler function is ??__
	- whenever signum is delivered to the proc 
		- If the disposition is set to SIG_IGN, then the signal is ignored
		- If the disposition is set to SIG_DFL, then the default action associated with the signal
		- If the disposition is set to a function ...
	- return: success [previous value of the signal handler]; failure [SIG_ERR]

## `int stat(const char *path, struct stat *statbuff)`
## `int fstat(int fd, struct stat *statbuff)`
## `int lstat(const char *path, struct stat *statbuff)`
	- `#include <sys/types.h>`
	- `#include <sys/stat.h>`
	- `#include <unistd.h>`
	- output information about a file, into the buffer pointed to by statbuff
		- `lstat()` is identical to `stat()` but can deal directly with symlinks
		- `fstat()` is identical to `stat()` but the file is specified by a descriptor
	- these all modify a `struct stat` with relevant data 
	- return : success [0], failure [-1]

## `pid_t wait(int *wstatus)`
## `pid_t waitpid(pid_t pid, int *wstatus, int options)`
	- `#include <sys/types.h>`
	- `#include <sys/wait.h>`
	- wait for a child proc to change states and obtain info on that
		- state changes : termination, signal stop, and signal resume
	- return : success [proc id], failure [-1]

## `pid_t wait3(int *wstatus, int options, struct rusage *rusage)`
## `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)`
	- `#include <sys/types.h>`
	- `#include <sys/wait.h>`
	- `#include <sys/resource.h>`
	- `#include <sys/time.h>`
	- these are nonstandard. `waitpid()`, and `waitid()` are preferable.
	- these return resource usage about the subproc
	- wait for a child proc to change states and obtain info on that
		- state changes : termination, signal stop, and signal resume
	- return : 'as for `man 2 waitpid`'

## `ssize_t write(int fd, const void *buf, size_t lenth)`
	- `#include <unistd.h>`
	- attempts to write up to `length` bytes from a buffer starting at `buf` to the file refered to by `fd`
	- return : success [number of bytes], failure [-1]

# Library Calls (man 3)

## NEW
## `int fflush(FILE *stream)`
	- `#include <stdio.h>`
	- flush a stream -- "forces a write of all user-space buffered data for the given output or update stream via the stream's underlying write function"
	- if the stream argument is NULL, fflush() flushes all open output streams
	- return : success [0], failure [EOF]

## `char *getcwd(char *buf, size_t size)`
	- `#include <unistd.h>`
	- get current working dir -- return a null-terminated string containing an absolute pathname that is the current working directory of the calling process via buf if present
	- return : success [pointer to pathname string], failure [NULL]

## `ssize_t getline(char **lineptr, size_t *n, FILE *stream)`
	- `#include <stdio.h>`
	- _get delimited string input_ -- reads an entire line from stream, storing the address of the buffer containing the text into \*lineptr
		- If \*lineptr is set to NULL and \*n is set 0 before the call, then getline() will allocate a buffer for storing the line. This buffer should be _always_ freed 
	- return : success [number of chars read], failure [-1]

## `int isatty(int fd)`
	- `#include <unistd.h>`
	- _test weather fd is open and refers to a terminal_ 
	- return : true [1], false [0]

## `char *strtok(char *str, const char *delim)`
	- `#include <string.h>`
	- _extract tokens from string_ -- breaks a string into a sequence of zero or more nonempty tokens
	- ON THE FIRST CALL TO STRTOK(), THE STRING TO BE PARSED SHOULD BE SPECIFIED IN STR. IN EACH SUBSEQUENT CALL THAT SHOULD PARSE THE SAME STRING, STR MUST BE NULL
	- Each call to strtok() returns a pointer to a null-terminated string containing the next token until NULL
	- delim specifies a set of bytes that delimit the tokens in the parsed string
		- The caller may specify different strings in delim in successive calls that parse the same string
	- return : pointer to next token or NULL

## `void perror(const char *s)`
	- `#include <stdio.h>`
	- _print a sys error message_ -- produces a message on standard error describing the last error encountered during a call to a system or library function
	- To be of most use, the argument string should include the name of the function that incurred the error

## `struct dirent *readdir(DIR *dirp)`
	- `#include <dirent.h>`
	- _read a dir_ -- returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp
	- data returned by readdir() may be overwritten by subsequent calls to readdir() for the same directory stream
	- return : success [pointer to next dirent struct]; failure or end [NULL]

## `DIR *opendir(const char *name)`
	- `#include <dirent.h>`
	- `#include <sys/types.h>`
	- _open a dir_ -- opens a directory stream corresponding to the directory name
	- stream is positioned at the first entry in the directory
	- return : success [pointer to the dir stream]; failure [NULL]

## `int closedir(DIR *dirp)`
	- `#include <dirent.h>`
	- `#include <sys/types.h>`
	- _close a dir_ -- closes the directory stream and file desc associated with dirp
	- return : success [0]; failure [-1]

## OLD

## `malloc()`
## `free()`
## `exit()`

## `putchar()`
## `printf()`
## `fprintf()`
## `vfprintf()`
## `sprintf()`
