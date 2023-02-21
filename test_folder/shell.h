#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int status;
extern char **environ;

int wordCount(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char **tokenize(char *str);
int execute(char **tokens);
void free_array(char **array);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

#endif
