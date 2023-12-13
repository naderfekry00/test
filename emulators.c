#include "shell.h"

/**
 * my_exit - exits the shell
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if my_info->argv[0] != "exit"
 */
int my_exit(my_info_t *my_info)
{
    int exitcheck;

    if (my_info->argv[1])  /* If there is an exit argument */
    {
        exitcheck = my_erratoi(my_info->argv[1]);
        if (exitcheck == -1)
        {
            my_info->status = 2;
            my_print_error(my_info, "Illegal number: ");
            my_eputs(my_info->argv[1]);
            my_eputchar('\n');
            return (1);
        }
        my_info->err_num = my_erratoi(my_info->argv[1]);
        return (-2);
    }
    my_info->err_num = -1;
    return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_cd(my_info_t *my_info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        my_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!my_info->argv[1])
    {
        dir = my_getenv(my_info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = my_getenv(my_info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (my_strcmp(my_info->argv[1], "-") == 0)
    {
        if (!my_getenv(my_info, "OLDPWD="))
        {
            my_puts(s);
            my_putchar('\n');
            return (1);
        }
        my_puts(my_getenv(my_info, "OLDPWD=")), my_putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = my_getenv(my_info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(my_info->argv[1]);
    if (chdir_ret == -1)
    {
        my_print_error(my_info, "can't cd to ");
        my_eputs(my_info->argv[1]), my_eputchar('\n');
    }
    else
    {
        my_setenv(my_info, "OLDPWD", my_getenv(my_info, "PWD="));
        my_setenv(my_info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * my_help - changes the current directory of the process
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_help(my_info_t *my_info)
{
    char **arg_array;

    arg_array = my_info->argv;
    my_puts("help call works. Function not yet implemented \n");
    if (0)
        my_puts(*arg_array); /* temp att_unused workaround */
    return (0);
}
