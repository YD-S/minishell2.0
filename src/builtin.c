/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:14:51 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/04 10:27:45 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_dir(void)
{
	int		i;
	char	*dir;

	dir = getcwd(NULL, sizeof(char *));
	i = ft_strlen(dir);
	if (dir == NULL)
		ft_printf("Error: getcwd() failed\n");
	while (dir[i] != '/')
		i--;
	i++;
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
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (args[i] != NULL && ft_strcmp(args[i], "$?") == 0)
	{
		ft_printf("%d\n", g_global.exit_status);
		return ;
	}
	while (args[i])
	{
		args[i] = ft_strtrim(args[i], "\"\'");
		if (ft_strcmp(args[i], "-n") != 0)
			print_args(args, i);
		else
			option = 1;
		i++;
	}
	if (!option)
		ft_printf("\n");
}

void	update_pwd(void)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, sizeof(char *));
	oldpwd = ft_get_env("$PWD");
	search_and_replace(g_global.envp, "$OLDPWD", oldpwd);
	search_and_replace(g_global.envp, "$PWD", pwd);
}

void	execute_cd(char **args)
{
	char	*path;

	if (ft_charpplen(args) == 1)
	{
		path = ft_get_env("$HOME");
		if (path == NULL)
			ft_printf("Error: HOME not set\n");
		else
		{
			chdir(path);
			update_pwd();
			get_dir();
		}
	}
	else if (ft_charpplen(args) > 2)
		ft_printf("Error: too many arguments\n");
	else
	{
		if (chdir(args[1]) != -1)
		{
			update_pwd();
			get_dir();
		}
		else
			ft_printf("Error: %s: %s\n", args[1], strerror(errno));
	}
}
