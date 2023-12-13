#include "shell.h"

/**
 * my_get_environ - returns the string array copy of our environ
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **my_get_environ(my_info_t *my_info)
{
    if (!my_info->environ || my_info->env_changed)
    {
        my_info->environ = my_list_to_strings(my_info->env);
        my_info->env_changed = 0;
    }

    return (my_info->environ);
}

/**
 * my_unsetenv - Remove an environment variable
 * @my_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int my_unsetenv(my_info_t *my_info, char *var)
{
    my_list_t *node = my_info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = my_starts_with(node->str, var);
        if (p && *p == '=')
        {
            my_info->env_changed = my_delete_node_at_index(&(my_info->env), i);
            i = 0;
            node = my_info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (my_info->env_changed);
}

/**
 * my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @my_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int my_setenv(my_info_t *my_info, char *var, char *value)
{
    char *buf = NULL;
    my_list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(my_strlen(var) + my_strlen(value) + 2);
    if (!buf)
        return (1);
    my_strcpy(buf, var);
    my_strcat(buf, "=");
    my_strcat(buf, value);
    node = my_info->env;
    while (node)
    {
        p = my_starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            my_info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    my_add_node_end(&(my_info->env), buf, 0);
    free(buf);
    my_info->env_changed = 1;
    return (0);
}
