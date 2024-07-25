#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 128


extern char **environ;

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> 
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>

int count_tokens(char *input, char *delims);
char **create_tok_array(char *input, char *delims, int toklen);
char *get_path(char *cmdname);
int run_cmd(char *cmdpath, char **usr_input);

#endif
