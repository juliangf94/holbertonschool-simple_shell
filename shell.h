#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Prototypes */
char *_which(char *command);
char *_getenv(const char *name);
void execute(char **argv);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);

/* Cœur du Shell */
void execute_command(char *full_path, char **argv);
void print_env(void);
#endif /* SHELL_H */
