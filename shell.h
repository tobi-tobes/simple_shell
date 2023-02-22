#ifndef _HEADER_
#define _HEADER_

#define BUFSIZE 1024

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * struct built_ins - Struct built_ins
 *
 * @command: The built-in command
 * @p: The function associated with the command
 */
typedef struct built_ins
{
	char *command;
	int (*p)(char **args);
} b_t;

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _atoi(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char **args, char *string, char del, int length);
int word_count(char *str, char del);
char **tokenize(char *str, char del);
int execute(char **tokens);
void free_array(char **array);
int check_num_arg(char **args);
char *_getenv(char *variable);
char **_update(char **args, char *path);
int search_PATH(char **args);
char **rmv_from_array(char **array, unsigned int position);
char **add_to_array(char **array, unsigned int new_size, char *buffer);
char **_update_env(char **env_array, char *buffer);
char *_update_env_var(char *env_var, char *variable);
int hsh_exit(char **args);
int hsh_env(char **args);
int hsh_setenv(char **args);
int hsh_unsetenv(char **args);
int handle_cmd_sep(char *string);
int handle_log_and(char *string);
int handle_log_or(char *string);
int cd_getenv(char *variable);
char *update_pwd(char *new_value);
int hsh_cd(char **args);
int chck_mul_cmds(char *string);
int call(char **args);

#endif
