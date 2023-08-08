/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:22:03 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/08 12:49:49 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_command2(t_pipex *p, int fd[2])
{
	if (!get_builtin(p->args[p->i][0]))
	{
		if (ft_open_in_file(p, fd))
		{
			if (execve(p->paths[p->i], p->args[p->i], g_global.env) == -1)
			{
				ft_write_error("cmd", strerror(errno), p->args[p->i][0]);
				return (g_global.exit_status = 127, 0);
			}
		}
		else
			return (g_global.exit_status = 127, 0);
	}
	else
		exit(EXIT_SUCCESS);
	return (g_global.exit_status = 0, 1);
}

int	ft_do_command(t_pipex *p, int fd[2], int fd2[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		ft_open_out_file(p, fd2);
		if (!ft_do_command2(p, fd))
			return (0);
	}
	else
	{
		while (waitpid(pid, NULL, 0) != pid)
			;
		close(fd2[1]);
	}
	return (g_global.exit_status = 0, 1);
}

void	ft_do_commands2(t_pipex *p, int n_com)
{
	int	fd[2];
	int	fd2[2];

	pipe(fd);
	p->i = 0;
	if (!ft_do_first_comm(p, fd, n_com))
		exit(EXIT_FAILURE);
	p->i = 1;
	while (p->i < n_com - 1)
	{
		if (!get_builtin(p->args[p->i][0]))
		{
			pipe(fd2);
			if (!ft_do_command(p, fd, fd2))
				exit(EXIT_FAILURE);
			fd[0] = fd2[0];
		}
		p->i++;
	}
	if (n_com > 1)
	{
		if (!ft_do_last_comm(p, fd))
			exit(EXIT_FAILURE);
	}
}

int	ft_do_commands(t_pipex *p, int n_com)
{
	pid_t	pid;

	if (n_com == 1 && get_builtin(p->args[0][0]))
		execute_builtin(p->args[0]);
	else if (n_com == 1 && p->command_not_found[0])
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			if (execve(p->paths[0], p->args[0], g_global.env) == -1)
			{
				ft_write_error("cmd", strerror(errno), p->args[0][0]);
				return (g_global.exit_status = 127, 0);
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
		ft_do_commands2(p, n_com);
	return (1);
}
