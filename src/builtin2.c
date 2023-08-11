/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:58 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/11 19:33:25 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(int flag)
{
	t_list	*aux;
	t_envp	*env;
	int		i;

	aux = g_global.envp;
	while (aux)
	{
		if (flag == 1)
			ft_printf("declare -x ");
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
	g_global.exit_status = 0;
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
	t_envp	*var;

	i = 1;
	var = ft_calloc(1, sizeof(t_envp));
	if (!args[i])
		execute_env(1);
	else if (ft_strchr(args[i], '='))
	{
		assign_var(var, args[i]);
		if (!search_var(var->key))
		{
			while (args[i])
			{
				get_new_var(*var);
				if (ft_strcmp(args[i], "$PATH") == 0)
					set_temp_path();
				i++;
			}
		}
		else
			search_and_replace(g_global.envp, var->key, var->value);
	}
	free(var->key);
	free(var->value);
	free(var);
	g_global.exit_status = 0;
}

int	is_digit_in_array(char *num)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (num[i])
	{
		res = ft_isdigit(num[i]);
		i++;
	}
	return (res);
}

void	execute_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		do_exit(0);
	else if (i == 2)
	{
		if (is_digit_in_array(args[1]))
			do_exit(ft_atoi(args[1]));
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				args[1]);
			do_exit(255);
		}
	}
	else
	{
		ft_printf("minishell: exit: too many arguments\n");
		g_global.exit_status = 1;
	}
}
