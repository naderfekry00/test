#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define MY_READ_BUF_SIZE 1024
#define MY_WRITE_BUF_SIZE 1024
#define MY_BUF_FLUSH -1

#define MY_CMD_NORM 0
#define MY_CMD_OR 1
#define MY_CMD_AND 2
#define MY_CMD_CHAIN 3

#define MY_CONVERT_LOWERCASE 1
#define MY_CONVERT_UNSIGNED 2

#define MY_USE_GETLINE 0
#define MY_USE_STRTOK 0

#define MY_HIST_FILE ".my_shell_history"
#define MY_HIST_MAX 4096

extern char **my_environ;

typedef struct my_liststr
{
    int num;
    char *str;
    struct my_liststr *next;
} my_list_t;

typedef struct my_passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    my_list_t *env;
    my_list_t *history;
    my_list_t *alias;
    char **my_environ;
    int env_changed;
    int status;

    char **my_cmd_buf;
    int my_cmd_buf_type;
    int readfd;
    int histcount;
} my_info_t;

#define MY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

typedef struct my_builtin
{
    char *type;
    int (*func)(my_info_t *);
} my_builtin_table;

int my_shell(my_info_t *, char **);
int find_my_builtin(my_info_t *);
void find_my_cmd(my_info_t *);
void fork_my_cmd(my_info_t *);

int is_my_cmd(my_info_t *, char *);
char *my_dup_chars(char *, int, int);
char *find_my_path(my_info_t *, char *, char *);

int my_loophsh(char **);

void my_eputs(char *);
int my_eputchar(char);
int my_putfd(char c, int fd);
int my_putsfd(char *str, int fd);

int my_strlen(char *);
int my_strcmp(char *, char *);
char *my_starts_with(const char *, const char *);
char *my_strcat(char *, char *);

char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

char **my_strtow(char *, char *);
char **my_strtow2(char *, char);

char *my_memset(char *, char, unsigned int);
void my_ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

int my_bfree(void **);

int my_interactive(my_info_t *);
int my_is_delim(char, char *);
int my_isalpha(int);
int my_atoi(char *);

int my_erratoi(char *);
void my_print_error(my_info_t *, char *);
int my_print_d(int, int);
char *my_convert_number(long int, int, int);
void my_remove_comments(char *);

int my_myexit(my_info_t *);
int my_mycd(my_info_t *);
int my_myhelp(my_info_t *);

int my_myhistory(my_info_t *);
int my_myalias(my_info_t *);

ssize_t my_get_input(my_info_t *);
int my_getline(my_info_t *, char **, size_t *);
void my_sigintHandler(int);

void my_clear_info(my_info_t *);
void my_set_info(my_info_t *, char **);
void my_free_info(my_info_t *, int);

char *my_getenv(my_info_t *, const char *);
int my_myenv(my_info_t *);
int my_mysetenv(my_info_t *);
int my_myunsetenv(my_info_t *);
int my_populate_env_list(my_info_t *);

char **my_get_environ(my_info_t *);
int my_unsetenv(my_info_t *, char *);
int my_setenv(my_info_t *, char *, char *);

char *my_get_history_file(my_info_t *my_info);
int my_write_history(my_info_t *my_info);
int my_read_history(my_info_t *my_info);
int my_build_history_list(my_info_t *my_info, char *buf, int linecount);
int my_renumber_history(my_info_t *my_info);

my_list_t *my_add_node(my_list_t **, const char *, int);
my_list_t *my_add_node_end(my_list_t **, const char *, int);
size_t my_print_list_str(const my_list_t *);
int my_delete_node_at_index(my_list_t **, unsigned int);
void my_free_list(my_list_t **);

size_t my_list_len(const my_list_t *);
char **my_list_to_strings(my_list_t *);
size_t my_print_list(const my_list_t *);
my_list_t *my_node_starts_with(my_list_t *, char *, char);
ssize_t my_get_node_index(my_list_t *, my_list_t *);

int my_is_chain(my_info_t *, char *, size_t *);
void my_check_chain(my_info_t *, char *, size_t *, size_t, size_t);
int my_replace_alias(my_info_t *);
int my_replace_vars(my_info_t *);
int my_replace_string(char **, char *);

#endif
