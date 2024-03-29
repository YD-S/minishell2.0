/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:14:10 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/17 18:30:21 by alvalope         ###   ########.fr       */
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

void	free_strs(char **result, int index)
{
	while (index-- > 0)
		free(result[index]);
	free(result);
}

void	do_call(t_pipex *p, t_aux auxs, char **argv, int argc)
{
	ft_reserve_mem(p, auxs.pipes + 1, ft_count_max_args(argv, argc, auxs.i));
	ft_count_args(argv, argc, p);
}

char	*if_no_builtin2(char *temp, char *temp2)
{
	if (temp[0] == '"' && temp[ft_strlen(temp) - 1] == '"')
		temp2 = ft_strtrim(temp, "\"");
	else if (temp[0] == '\'' && temp[ft_strlen(temp) - 1] == '\'')
		temp2 = ft_strtrim(temp, "'");
	return (temp2);
}

void	if_no_builtin(t_pipex *p, t_aux *auxs, char **argv, char **paths)
{
	char	*temp;
	char	*temp2;

	temp = ft_strdup(argv[auxs->i]);
	temp2 = NULL;
	temp2 = if_no_builtin2(temp, temp2);
	if (temp2)
	{
		p->paths[auxs->cmd] = ft_check_comm(paths, temp2, p, auxs->cmd);
		if (!p->command_not_found[auxs->cmd])
			free(temp2);
		free(temp);
		return ;
	}
	else if (paths)
		p->paths[auxs->cmd] = ft_check_comm(paths, temp, p, auxs->cmd);
	else
	{
		p->paths[auxs->cmd] = ft_strdup(temp);
		if (p->command_not_found[auxs->cmd])
			free(temp);
	}
	if (!p->command_not_found[auxs->cmd])
		free(temp);
}
