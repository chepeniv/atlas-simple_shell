# EXERCISES
- these exercises are pulled from the intranet concept page [everything you need to know to start coding your own shell](https://intranet.atlasschool.com/concepts/900)
- besides the suggested exercises, i also plan on playing with the given examples

## PID, PPID
- [x] "Write a program that prints the PID of the parent process"

## ARGUMENTS
- [x] "Write a program that prints all the arguments, without using ac"
- [x] "Write a program that prints "$ ", wait for the user to enter a command, prints it on the next line." `getline`
- [x] "a function that splits a string and returns an array of each word of the string" `strtok`

## EXEC A PROG
- `NULL`

## CREATING PROC
- `NULL`

## WAIT
- [ ] "Write a program that executes the command ls -l /tmp in 5 different child processes. Each child should be created by the same process (the father). Wait for a child to exit before creating a new child."

## FILE INFO
- [ ] "Write a program that looks for files in the current PATH"

## ENVIRONMENT
### main()
- [ ] Write a program that prints the environment using the global variable environ.
- [ ] Write a program that prints the address of env (the third parameter of the main function) and environ (the global variable). Are they they same? Does this make sense?
- [ ] Write a function that gets an environment variable. (without using getenv)
    - `char *_getenv(const char *name);`
	- `man 3 getenv`
- [ ] Write a function that prints each directory contained in the the environment variable PATH, one directory per line.
- [ ] Write a function that builds a linked list of the PATH directories.
- [ ] Write a function that changes or adds an environment variable (without using setenv).
	- `int _setenv(const char *name, const char *value, int overwrite);`
	- `man 3 setenv`
- [ ] Write a function that deletes the variable name from the environment (without using unsetenv).
	- `int _unsetenv(const char *name);`

