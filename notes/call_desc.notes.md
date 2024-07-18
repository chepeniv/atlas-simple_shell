File/Directory Operations:
	open:			Opens a file or device.
	close:			Closes an open file descriptor.
	read:			Reads from an open file descriptor.
	write:			Writes to an open file descriptor.
	opendir:		Opens a directory stream.
	closedir:		Closes a directory stream.
	readdir:		Reads directory entries from a directory stream.
	access:			Checks if a file or directory exists and has certain permissions.
	chdir:			Changes the current working directory.
	getcwd:			Gets the current working directory path.
	stat, lstat, fstat:
					Get file information (like size, permissions, etc.).

Process Management:
	fork:			Creates a new child process.
	execve:			Replaces the current process with a new program.
	exit, _exit:	Terminates the calling process.
	getpid:			Gets the process ID of the current process.
	wait, waitpid, wait3, wait4:
					Waits for a child process to terminate.
	kill:			Sends a signal to a process.
	signal:			Sets up a handler for a signal.

I/O (Input/Output):
	printf, fprintf, vfprintf:
					Print formatted output to stdout, a file, or a variable argument list respectively.
	sprintf:		Print formatted output to a string.
	putchar:		Writes a single character to stdout.
	getline:		Reads a line of text from a file or stream.
	fflush:			Flushes output buffers.
	perror:			Prints an error message to stderr.
	isatty:			Checks if a file descriptor refers to a terminal.
	
Memory Management:
	malloc:			Allocates a block of memory on the heap.
	free:			Deallocates a block of memory previously allocated by malloc.

String Manipulation:
	strtok:			Breaks a string into a sequence of tokens based on a delimiter.

Important Notes:
	man pages: The "man 2" or "man 3" after each function refers to the section of the Unix manual pages where you can find detailed information about that function. Type man 2 open or man 3 printf in your terminal to learn more.
	Header files: You'll need to include the appropriate header files in your C code to use these functions. For example, unistd.h for file and process operations, stdio.h for input/output functions, and stdlib.h for memory management functions.
