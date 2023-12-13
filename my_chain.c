#include "shell.h"

/**
 * my_is_chain - test if current char in buffer is a chain delimiter
 * @my_info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int my_is_chain(my_info_t *my_info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        my_info->my_cmd_buf_type = MY_CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        my_info->my_cmd_buf_type = MY_CMD_AND;
    }
    else if (buf[j] == ';') /* found end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        my_info->my_cmd_buf_type = MY_CMD_CHAIN;
    }
    else
        return (0);
    *p = j;
    return (1);
}

/**
 * my_check_chain - checks if we should continue chaining based on last status
 * @my_info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void my_check_chain(my_info_t *my_info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (my_info->my_cmd_buf_type == MY_CMD_AND)
    {
        if (my_info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (my_info->my_cmd_buf_type == MY_CMD_OR)
    {
        if (!my_info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * my_replace_alias - replaces an aliases in the tokenized string
 * @my_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int my_replace_alias(my_info_t *my_info)
{
    int i;
    my_list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = my_node_starts_with(my_info->alias, my_info->argv[0], '=');
        if (!node)
            return (0);
        my_free(my_info->argv[0]);
        p = my_strchr(node->str, '=');
        if (!p)
            return (0);
        p = my_strdup(p + 1);
        if (!p)
            return (0);
        my_info->argv[0] = p;
    }
    return (1);
}

/**
 * my_replace_vars - replaces vars in the tokenized string
 * @my_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int my_replace_vars(my_info_t *my_info)
{
    int i = 0;
    my_list_t *node;

    for (i = 0; my_info->argv[i]; i++)
    {
        if (my_info->argv[i][0] != '$' || !my_info->argv[i][1])
            continue;

        if (!my_strcmp(my_info->argv[i], "$?"))
        {
            my_replace_string(&(my_info->argv[i]),
                              my_strdup(my_convert_number(my_info->status, 10, 0)));
            continue;
        }
        if (!my_strcmp(my_info->argv[i], "$$"))
        {
            my_replace_string(&(my_info->argv[i]),
                              my_strdup(my_convert_number(getpid(), 10, 0)));
            continue;
        }
        node = my_node_starts_with(my_info->env, &my_info->argv[i][1], '=');
        if (node)
        {
            my_replace_string(&(my_info->argv[i]),
                              my_strdup(my_strchr(node->str, '=') + 1));
            continue;
        }
        my_replace_string(&my_info->argv[i], my_strdup(""));
    }
    return (0);
}

/**
 * my_replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int my_replace_string(char **old, char *new)
{
    my_free(*old);
    *old = new;
    return (1);
}
