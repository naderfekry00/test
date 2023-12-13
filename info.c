#include "shell.h"

/**
 * my_clear_info - initializes my_info_t struct
 * @info: struct address
 */
void my_clear_info(my_info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * my_set_info - initializes my_info_t struct
 * @info: struct address
 * @av: argument vector
 */
void my_set_info(my_info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = my_strtow(info->arg, " \t");
        if (!info->argv)
        {

            info->argv = my_malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = my_strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        my_replace_alias(info);
        my_replace_vars(info);
    }
}

/**
 * my_free_info - frees my_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void my_free_info(my_info_t *info, int all)
{
    my_ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->my_cmd_buf)
            my_free(info->arg);
        if (info->env)
            my_free_list(&(info->env));
        if (info->history)
            my_free_list(&(info->history));
        if (info->alias)
            my_free_list(&(info->alias));
        my_ffree(info->my_environ);
        info->my_environ = NULL;
        my_bfree((void **)info->my_cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        my_putchar(MY_BUF_FLUSH);
    }
}
