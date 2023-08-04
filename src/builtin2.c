/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:26:58 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/04 10:28:37 by alvalope         ###   ########.fr       */
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
		execute_env(1);
	else if (ft_strchr(args[i], '='))
	{
		key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
		key = ft_strjoin("$", key);
		value = ft_strtrim(ft_substr(args[i], ft_strchr(args[i], '=') - args[i]
					+ 1, ft_strlen(args[i]) - ft_strlen(key)), "\"\'");
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

void	execute_exit(void)
{
	exit(EXIT_SUCCESS);
}
