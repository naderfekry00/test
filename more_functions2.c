#include "shell.h"

/**
 * my_erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int my_erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++; /* TODO: why does this make main return 255? */
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * my_print_error - prints an error message
 * @my_info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void my_print_error(my_info_t *my_info, char *estr)
{
    my_eputs(my_info->fname);
    my_eputs(": ");
    my_print_d(my_info->line_count, STDERR_FILENO);
    my_eputs(": ");
    my_eputs(my_info->my_cmd_buf[0]);
    my_eputs(": ");
    my_eputs(estr);
}

/**
 * my_print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int my_print_d(int input, int fd)
{
    int (*my_putchar_func)(char) = my_putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        my_putchar_func = my_eputchar;
    if (input < 0)
    {
        _abs_ = -input;
        my_putchar_func('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            my_putchar_func('0' + current / i);
            count++;
        }
        current %= i;
    }
    my_putchar_func('0' + current);
    count++;

    return (count);
}

/**
 * my_convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *my_convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & MY_CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';

    }
    array = flags & MY_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * my_remove_comments - function replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void my_remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}
