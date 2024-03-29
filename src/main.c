/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:59:03 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/16 21:25:00 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char	*line;
	char	**cmds;
	int		check;

	if (argc != 1)
		exit(0);
	ft_init_global(envp);
	g_global.env = ft_charppdup((const char **)envp);
	call_signal();
	while (1)
	{
		line = ft_readline();
		check = ft_check_cmd(line);
		if (check == 1)
		{
			cmds = ft_parser(line);
			ft_executer(cmds, g_global.path);
			ft_charppfree(cmds);
			free(line);
		}
		else if (check == 0)
			ft_error("minishell syntax error\n", line);
	}
}

t_envp	*ft_get_node(char *str)
{
	t_list	*list;
	t_envp	*node;

	list = g_global.envp;
	while (list)
	{
		node = list->content;
		if (!ft_strcmp(str, node->key))
			return (free(str), node);
		list = list->next;
	}
	return (free(str), NULL);
}

void	ft_aux_get_var(t_master *mas)
{
	mas->strs.aux2 = ft_strchrs(mas->strs.aux + 1, " $=\n\t?\'\"|");
	mas->var = ft_get_node(ft_substr(mas->strs.cpy, ft_get_index(mas->strs.cpy,
					mas->strs.aux), ft_get_index(mas->strs.cpy, mas->strs.aux2)
				- ft_get_index(mas->strs.cpy, mas->strs.aux)));
	if (!mas->var)
		mas->strs.cpy = ft_replace(mas->strs.cpy, mas->strs.aux, mas->strs.aux2,
				"");
	else
	{
		mas->strs.cpy = ft_replace(mas->strs.cpy, mas->strs.aux, mas->strs.aux2,
				mas->var->value);
		mas->count.i = mas->count.j + (int)ft_strlen(mas->var->value);
	}
}

char	*ft_get_var(char *cmd)
{
	t_master	mas;

	init_all(&mas, cmd);
	if (cmd[0] == SQ && condition2(cmd, mas))
		return (mas.strs.cpy);
	while (mas.strs.cpy[mas.count.i])
	{
		if (condition3(mas))
		{
			if_dollar_int(&mas);
			continue ;
		}
		mas.strs.aux = ft_strchr(mas.strs.cpy + mas.count.i, '$');
		if (!mas.strs.aux)
			break ;
		mas.count.j = ft_get_index(mas.strs.cpy,
				ft_strchr(mas.strs.cpy + mas.count.i, '$'));
		if (ft_isspace(mas.strs.aux[1]) || condition(mas))
		{
			mas.count.i++;
			continue ;
		}
		ft_aux_get_var(&mas);
	}
	return (mas.strs.cpy);
}

void	do_exit(int status)
{
	free_env();
	exit(status);
}
