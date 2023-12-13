#include "shell.h"

/**
 * my_main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int my_main(int ac, char **av)
{
    my_info_t info[] = {MY_INFO_INIT};
    int fd = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                my_eputs(av[0]);
                my_eputs(": 0: Can't open ");
                my_eputs(av[1]);
                my_eputchar('\n');
                my_eputchar(MY_BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = fd;
    }
    my_populate_env_list(info);
    my_read_history(info);
    my_shell(info, av);
    return (EXIT_SUCCESS);
}
