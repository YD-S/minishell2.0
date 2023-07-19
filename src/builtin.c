/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:14:51 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/18 12:12:26 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_export(char **args)
{
	char	**var;
	t_envp	*env;
	//t_list	*aux_l;
	//t_envp	*aux_e;

	ft_printf("A:%s\n", args[1]);

	var = ft_split(args[1], '=');
	/*if (var[1])
	{*/
		env = ft_calloc(1, sizeof(t_envp));
		env->key = ft_strjoin("$", var[0]);
		//env->value = var[1];
		ft_printf("V:%s\n", env->key);
		ft_printf("B:%s\n", var[1]);
		env->value = ft_strtrim(var[1], "\"\'");
		ft_printf("V:%s\n", env->value);
		/*aux_l = g_global.envp;
		ft_lstadd_back(&g_global.envp, ft_lstnew(env));
		while (aux_l)
		{
			aux_e = aux_l->content;
			ft_printf("%s\n", aux_e->key);
			if (ft_strcmp(aux_e->key, var[0]) == 0)
				del_env();
			aux_l = aux_l->next;
		}*/
	//}
}
