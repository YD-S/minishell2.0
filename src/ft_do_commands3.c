/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:55 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/16 11:00:28 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_commands2b(t_pipex *p, int fd[2], int fd2[2], int n_com)
{
	while (p->i < n_com - 1)
	{
		if (!get_builtin(p->args[p->i][0]))
		{
			pipe(fd2);
			if (!ft_do_command(p, fd, fd2))
				exit(EXIT_FAILURE);
			fd[0] = fd2[0];
		}
		else
		{
			pipe(fd2);
			ft_do_command2builtin(p, fd, fd2);
			fd[0] = fd2[0];
		}
		p->i++;
	}
}

int	ft_do_commands2(t_pipex *p, int n_com)
{
	int		fd[2];
	int		fd2[2];
	pid_t	pid;

	pipe(fd);
	p->i = 0;
	if (!ft_do_first_comm(p, fd, n_com))
		exit(EXIT_FAILURE);
	p->i = 1;
	ft_do_commands2b(p, fd, fd2, n_com);
	if (n_com > 1)
	{
		pid = 0;
		if (!ft_do_last_comm(p, fd, pid))
			exit(EXIT_FAILURE);
	}
	return (1);
}
