#include "shell.h"

/**
 * my_env - prints the current environment
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(my_info_t *my_info)
{
    my_print_list_str(my_info->env);
    return (0);
}

/**
 * my_getenv - gets the value of an environ variable
 * @my_info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *my_getenv(my_info_t *my_info, const char *name)
{
    my_list_t *node = my_info->env;
    char *p;

    while (node)
    {
        p = my_starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @my_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_setenv(my_info_t *my_info)
{
    if (my_info->argc != 3)
    {
        my_eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (my_setenv(my_info, my_info->argv[1], my_info->argv[2]))
        return (0);
    return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @my_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_unsetenv(my_info_t *my_info)
{
    int i;

    if (my_info->argc == 1)
    {
        my_eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= my_info->argc; i++)
        my_unsetenv(my_info, my_info->argv[i]);

    return (0);
}

/**
 * my_populate_env_list - populates env linked list
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_populate_env_list(my_info_t *my_info)
{
    my_list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        my_add_node_end(&node, environ[i], 0);
    my_info->env = node;
    return (0);
}
