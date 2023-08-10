/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:14:10 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/10 19:45:54 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reserve_mem(t_pipex *p, int cmd, int max_args)
{
	int	i;

	i = 0;
	p->args = ft_calloc(sizeof(char **), cmd);
	while (i < cmd)
	{
		p->args[i] = ft_calloc(sizeof(char *), max_args + 1);
		i++;
	}
	p->infile = ft_calloc(sizeof(char *), cmd);
	p->outfl = ft_calloc(sizeof(char *), cmd);
	p->paths = ft_calloc(sizeof(char *), cmd);
	p->n_args = ft_calloc(sizeof(int), cmd);
	p->heredoc = ft_calloc(sizeof(int), cmd);
	p->outmode = ft_calloc(sizeof(int), cmd);
	p->command_not_found = ft_calloc(sizeof(int), cmd);
}

void	do_call(t_pipex *p, t_aux auxs, char **argv, int argc)
{
	ft_reserve_mem(p, auxs.pipes + 1, ft_count_max_args(argv, argc, auxs.i));
	ft_count_args(argv, argc, p);
}
