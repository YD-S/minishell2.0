/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:49:40 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/16 10:35:23 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_check_outfile(t_pipex *p, t_aux *auxs, char **argv)
{
	if (strncmp(argv[auxs->i], ">\0", 2) == 0)
	{
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		auxs->i += 2;
		return (1);
	}
	else if (strncmp(argv[auxs->i], ">>\0", 3) == 0)
	{
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		p->outmode[auxs->cmd] = 1;
		auxs->i += 2;
		return (1);
	}
	return (0);
}

void	ft_check_io_fl2(t_pipex *p, t_aux *auxs, char **argv, int file)
{
	if (p->outfl[auxs->cmd])
		free(p->outfl[auxs->cmd]);
	p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
	p->outmode[auxs->cmd] = 1;
	file = open(p->outfl[auxs->cmd], O_WRONLY | O_APPEND);
	close(file);
}

int	ft_check_io_fl(t_pipex *p, t_aux *auxs, char **argv, int file)
{
	if (strncmp(argv[auxs->i], ">\0", 2) == 0)
	{
		if (p->outfl[auxs->cmd])
			free(p->outfl[auxs->cmd]);
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		p->outmode[auxs->cmd] = 0;
		file = open(p->outfl[auxs->cmd], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(file);
	}
	else if (strncmp(argv[auxs->i], ">>\0", 3) == 0)
		ft_check_io_fl2(p, auxs, argv, file);
	else if (strncmp(argv[auxs->i], "<\0", 2) == 0)
		p->infile[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
	else if (strncmp(argv[auxs->i], "<<\0", 3) == 0)
		p->heredoc[auxs->cmd] = 1;
	else
		return (0);
	auxs->i += 2;
	return (1);
}
