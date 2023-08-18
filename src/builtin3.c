/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:37:13 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/06 00:38:26 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(void)
{
	char	*pwd;

	pwd = ft_get_env("$PWD");
	if (pwd == NULL)
	{
		ft_printf("Error: PWD not set\n");
		g_global.exit_status = 1;
	}
	else
		ft_printf("%s\n", pwd);
}

void	free_env_node(void *content)
{
	t_envp	*env_node;

	env_node = (t_envp *)content;
	free(env_node->key);
	free(env_node->value);
	free(env_node);
}

int	check_arg(char *arg)
{
	if (arg == NULL)
		return (0);
	if (ft_strcmp(arg, "$PATH") == 0)
	{
		ft_charppfree(g_global.path);
		g_global.path = NULL;
	}
	return (1);
}

void	ft_unset_env(char *arg)
{
	t_list	*current;
	t_list	*prev;
	t_envp	*env_node;

	if (!check_arg(arg))
		return ;
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
	int		i;
	char	*args_i;

	i = 1;
	while (args[i])
	{
		args_i = ft_strjoin("$", args[i]);
		if (ft_get_env(args_i) != NULL)
			ft_unset_env(args_i);
		free(args_i);
		i++;
	}
	g_global.exit_status = 0;
}
