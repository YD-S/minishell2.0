/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:14:51 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/22 21:08:09 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_dir(void)
{
	int		i;
	char	*dir;

	dir = getcwd(g_global.dir, sizeof(char *));
	i = ft_strlen(dir);
	if (dir == NULL)
		ft_printf("Error: getcwd() failed\n");
	while (dir[i] != '/')
		i--;
	i++;
	g_global.dir = ft_substr(dir, i, ft_strlen(dir));
}

void	execute_echo(char **args)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n") != 0)
		{
			if (i < ft_charpplen(args) - 1)
				ft_printf("%s ", args[i]);
			else
				ft_printf("%s", args[i]);
		}
		else
			option = 1;
		i++;
	}
	if (!option)
		ft_printf("\n");
}

void	execute_env(void)
{
	t_list	*aux;
	t_envp	*env;
	int		i;

	aux = g_global.envp;
	while (aux)
	{
		i = 0;
		env = aux->content;
		if (env->key[i] == '$')
			i++;
		while (env->key[i])
		{
			ft_printf("%c", env->key[i]);
			i++;
		}
		ft_printf("=");
		ft_printf("%s\n", env->value);
		aux = aux->next;
	}
}

int	search_var(char *key)
{
	t_envp	*aux;
	t_list	*list;

	list = g_global.envp;
	while (list)
	{
		aux = list->content;
		if (!ft_strcmp(aux->key, key))
			return (1);
		list = list->next;
	}
	return (0);
}

void	execute_export(char **args)
{
	int		i;
	char	*key;
	char	*value;
	t_envp	*new_var;

	i = 1;
	if (!args[i])
		execute_env();
	if (ft_strchr(args[i], '='))
	{
		key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
		key = ft_strjoin("$", key);
		value = ft_substr(args[i], ft_strchr(args[i], '=') - args[i] + 1,
				ft_strlen(args[i]) - ft_strlen(key));
		if (!search_var(key))
		{
			while (args[i])
			{
				new_var = ft_calloc(1, sizeof(t_envp));
				new_var->key = key;
				new_var->value = value;
				ft_lstadd_back(&g_global.envp, ft_lstnew(new_var));
				i++;
			}
		}
		else
			search_and_replace(g_global.envp, key, value);
	}
}
