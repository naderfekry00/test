#include "shell.h"

/**
 * my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @my_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(my_info_t *my_info)
{
    my_print_list(my_info->history);
    return (0);
}

/**
 * unset_my_alias - sets alias to string
 * @my_info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_my_alias(my_info_t *my_info, char *str)
{
    char *p, c;
    int ret;

    p = my_strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = my_delete_node_at_index(&(my_info->alias),
                                  my_get_node_index(my_info->alias,
                                                    my_node_starts_with(my_info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_my_alias - sets alias to string
 * @my_info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_my_alias(my_info_t *my_info, char *str)
{
    char *p;

    p = my_strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_my_alias(my_info, str));

    unset_my_alias(my_info, str);
    return (my_add_node_end(&(my_info->alias), str, 0) == NULL);
}

/**
 * print_my_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_my_alias(my_list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = my_strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            my_putchar(*a);
        my_putchar('\'');
        my_puts(p + 1);
        my_puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @my_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(my_info_t *my_info)
{
    int i = 0;
    char *p = NULL;
    my_list_t *node = NULL;

    if (my_info->argc == 1)
    {
        node = my_info->alias;
        while (node)
        {
            print_my_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; my_info->argv[i]; i++)
    {
        p = my_strchr(my_info->argv[i], '=');
        if (p)
            set_my_alias(my_info, my_info->argv[i]);
        else
            print_my_alias(my_node_starts_with(my_info->alias, my_info->argv[i], '='));
    }

    return (0);
}
