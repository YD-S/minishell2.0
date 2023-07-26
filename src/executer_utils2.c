/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:49:40 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/26 15:41:29 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **result, int index)
{
	while (index-- > 0)
		free(result[index]);
	free(result);
}

void	ft_free_mem(t_pipex *p, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd)
	{
		free(p->args[i]);
		if (p->paths[i])
			free(p->paths[i]);
		i++;
	}
	free(p->infile);
	free(p->outfl);
	free(p->paths);
	free(p->n_args);
	free(p->heredoc);
	free(p->outmode);
	free(p->args);
	free(p->command_not_found);
}

void	ft_write_error(char *type, char *error, char *obj)
{
	if (ft_strcmp(type, "cmd") == 0)
	{
		write(2, "bash: ", 6);
		write(2, obj, ft_strlen(obj));
		write(2, ": command not found\n", 21);
	}
	else if (ft_strcmp(type, "file") == 0)
	{
		write(2, "bash: ", 6);
		write(2, obj, ft_strlen(obj));
		write(2, ": ", 2);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
}
