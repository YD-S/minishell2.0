/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:14:51 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/06 00:18:45 by ysingh           ###   ########.fr       */
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
	else if(ft_strcmp(dir, ft_get_env("$HOME")) == 0)
	{
		g_global.dir = ft_strdup("~");
		free(dir);
		return ;
	}
	i = ft_strlen(dir);
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
		g_global.exit_status = 0;
		return ;
	}
	int j = 0;
	while (args[i])
	{
		while (args[i][j] == '-')
			j++;
		if (args[i][j] == 'n')
			option = 1;
		else
			print_args(args, i);
		i++;
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
	search_and_replace(g_global.envp, "$OLDPWD", oldpwd);
	search_and_replace(g_global.envp, "$PWD", pwd);
}

void	execute_cd(char **args)
{
	char	*path;

	if(search_var("$PWD") == 0 || ft_get_env("$PWD") == NULL)
	{
		ft_printf("Error: PWD not set\n");
		g_global.exit_status = 1;
		return ;
	}
	if (ft_charpplen(args) == 1 || ft_strcmp(args[1], "~") == 0)
	{
		path = ft_get_env("$HOME");
		if (path == NULL)
		{
			ft_printf("Error: HOME not set\n");
			g_global.exit_status = 1;
		}
		else
		{
			chdir(path);
			update_pwd();
			get_dir();
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_get_env("$OLDPWD");
		if (path == NULL || search_var("$OLDPWD") == 0)
		{
			ft_printf("Error: OLDPWD not set\n");
			g_global.exit_status = 1;
		}
		else
		{
			ft_printf("%s\n", path);
			chdir(path);
			update_pwd();
			get_dir();
		}
	}
	else if (chdir(args[1]) != -1)
	{
		update_pwd();
		get_dir();
	}
	else
	{
		ft_printf("Error: %s: %s\n", args[1], strerror(errno));
		g_global.exit_status = 1;
	}
}

void	execute_pwd(void)
{
	char *pwd;

	pwd = ft_get_env("$PWD");
	if (pwd == NULL)
	{
		ft_printf("Error: PWD not set\n");
		g_global.exit_status = 1;
	}
	else
		ft_printf("%s\n", pwd);

}

void free_env_node(void *content)
{
	t_envp *env_node;

	env_node = (t_envp *)content;
	free(env_node->key);
	free(env_node->value);
	free(env_node);
}

void ft_unset_env(char *arg)
{
	t_list	*current;
	t_list 	*prev;
	t_envp	*env_node;

	if(arg == NULL)
		return ;
	if(ft_strcmp(arg, "$PATH") == 0)
	{
		ft_charppfree(g_global.path);
		g_global.path = NULL;
	}
	current = g_global.envp;
	prev = NULL;
	while (current != NULL)
	{
		env_node = (t_envp *)current->content;
		if (ft_strcmp(env_node->key, arg) == 0)
		{
			if (prev == NULL)
				g_global.envp = current->next;
			else
				prev->next = current->next;
			free_env_node(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	execute_unset(char **args)
{
	int	i;
	char *args_i;

	i = 1;
	while (args[i])
	{
		args_i = ft_strjoin("$",args[i]);
		if (ft_get_env(args_i) != NULL)
			ft_unset_env(args_i);
		free(args_i);
		i++;
	}
	g_global.exit_status = 0;
}