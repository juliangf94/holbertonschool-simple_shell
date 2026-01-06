#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>/* Pour la gestion de Ctrl+C */

extern char **environ;

/* Prototypes */
char *_which(char *command);
void print_prompt(void);
int handle_line(char *line, char *prog_name, int counter, int last_status);
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *s);
int handle_builtins(char **argv, char *line, int last_status);
char *_resolve_path(char *cmd);
int _atoi(char *s);

/* Cœur du Shell */
int execute_command(char *full_path, char **argv);
void print_env(void);

/* Gestion des signaux */
void handle_sigint(int sig);

#endif /* SHELL_H */