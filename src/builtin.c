/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:14:51 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/17 18:39:58 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_dir(void)
{
	int		i;
	char	*dir;

	dir = getcwd(NULL, sizeof(char *));
	if (dir == NULL)
		ft_printf("Error: getcwd() failed\n");
	else if (ft_strcmp(dir, ft_get_env("$HOME")) == 0)
	{
		g_global.dir = ft_strdup("~");
		free(dir);
		return ;
	}
	i = ft_strlen(dir);
	while (dir[i] != '/')
		i--;
	i++;
	free(g_global.dir);
	g_global.dir = ft_substr(dir, i, ft_strlen(dir));
	free(dir);
}

void	print_args(char **args, int i)
{
	if (i < ft_charpplen(args) - 1)
		ft_printf("%s ", args[i]);
	else
		ft_printf("%s", args[i]);
}

void	execute_echo(char **args)
{
	t_count	count;
	int		option;

	count.i = 1;
	count.j = 0;
	option = 0;
	if (args[count.i] != NULL && ft_strcmp(args[count.i], "$?") == 0)
	{
		ft_printf("%d\n", g_global.exit_status);
		g_global.exit_status = 0;
		return ;
	}
	while (args[count.i])
	{
		while (args[count.i][count.j] == '-')
			count.j++;
		if (args[count.i][count.j] == 'n')
			option = 1;
		else
			print_args(args, count.i);
		count.i++;
	}
	if (!option)
		ft_printf("\n");
	g_global.exit_status = 0;
}

void	update_pwd(void)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, sizeof(char *));
	oldpwd = ft_get_env("$PWD");
	if (oldpwd && pwd)
	{
		search_and_replace(g_global.envp, "$OLDPWD", oldpwd);
		search_and_replace(g_global.envp, "$PWD", pwd);
	}
	free(pwd);
}

void	execute_cd(char **args)
{
	char	*path;

	path = NULL;
	if (ft_charpplen(args) == 1 || ft_strcmp(args[1], "~") == 0)
	{
		path = ft_get_env("$HOME");
		if (path == NULL)
			printg_status("Error: HOME not set", 1);
		else
			do_cd(path, 0);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_get_env("$OLDPWD");
		if (path == NULL || search_var("$OLDPWD") == 0)
			printg_status("Error: OLDPWD not set", 1);
		else
			do_cd(path, 1);
	}
	else
		do_cd(args[1], 0);
}
