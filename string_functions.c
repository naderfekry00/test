#include "shell.h"

/**
 * my_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int my_strlen(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (*str++)
        length++;
    return length;
}

/**
 * my_strcmp - performs lexicogarphic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int my_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * my_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *my_starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;
    return (char *)haystack;
}

/**
 * my_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return result;
}
