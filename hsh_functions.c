#include "shell.h"

/**
 * my_shell_loop - Main shell loop
 * @info: The parameter & return info struct
 * @av: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int my_shell_loop(my_info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		my_clear_info(info);
		if (my_interactive(info))
			my_puts("$ ");
		my_eputchar(MY_BUF_FLUSH);
		r = my_get_input(info);
		if (r != -1)
		{
			my_set_info(info, av);
			builtin_ret = find_my_builtin(info);
			if (builtin_ret == -1)
				find_my_cmd(info);
		}
		else if (my_interactive(info))
			my_putchar('\n');
		my_free_info(info, 0);
	}
	my_write_history(info);
	my_free_info(info, 1);
	if (!my_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
		handle_builtin_ret(info);
	return (builtin_ret);
}

/**
 * find_my_builtin - Finds a builtin command
 * @info: The parameter & return info struct
 *
 * Return: Builtin execution status
 */
int find_my_builtin(my_info_t *info)
{
	int i, built_in_ret = -1;
	my_builtin_table builtintbl[] = {
		{"exit", my_myexit},
		{"env", my_myenv},
		{"help", my_myhelp},
		{"history", my_myhistory},
		{"setenv", my_mysetenv},
		{"unsetenv", my_myunsetenv},
		{"cd", my_mycd},
		{"alias", my_myalias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (my_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * handle_builtin_ret - Handles the return status of a builtin command
 * @info: The parameter & return info struct
 */
void handle_builtin_ret(my_info_t *info)
{
	if (info->err_num == -1)
		exit(info->status);
	exit(info->err_num);
}
