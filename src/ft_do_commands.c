/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:22:03 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/17 18:25:16 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_command2builtin(t_pipex *p, int fd[2], int fd2[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		ft_open_out_file(p, fd2);
		ft_open_in_file(p, fd);
		status = 0;
		execute_builtin(p, fd2, status, p->i);
		close(fd[0]);
	}
	else
	{
		while (waitpid(pid, &status, 0) != pid)
			;
		close(fd2[1]);
		if (WIFEXITED(status))
			g_global.exit_status = WEXITSTATUS(status);
	}
	return (1);
}

int	ft_do_command2(t_pipex *p, int fd[2])
{
	if (!get_builtin(p->args[p->i][0]))
	{
		if (ft_open_in_file(p, fd))
		{
			if (execve(p->paths[p->i], p->args[p->i], g_global.env) == -1)
			{
				ft_write_error("cmd", strerror(errno), p->args[p->i][0]);
				g_global.exit_status = 127;
				free_env();
				return (0);
			}
		}
		else
		{
			g_global.exit_status = 127;
			free_env();
			return (0);
		}
	}
	return (1);
}

int	ft_do_command(t_pipex *p, int fd[2], int fd2[2])
{
	pid_t	pid;
	int		status;

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
		while (waitpid(pid, &status, 0) != pid)
			;
		close(fd2[1]);
		if (WIFEXITED(status))
			g_global.exit_status = 127;
	}
	return (1);
}

int	ft_do_one_command(t_pipex *p)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (execve(p->paths[0], p->args[0], g_global.env) == -1)
		{
			ft_write_error("cmd", strerror(errno), p->args[0][0]);
			free_env();
			g_global.exit_status = 127;
			return (0);
		}
	}
	else
	{
		while (waitpid(pid, &status, 0) != pid)
			;
		if (WIFEXITED(status))
			g_global.exit_status = 127;
	}
	return (1);
}

int	ft_do_commands(t_pipex *p, int n_com)
{
	int	fd[2];
	int	status;

	status = 1;
	if (n_com == 1 && get_builtin(p->args[0][0]))
		execute_builtin(p, fd, status, 0);
	else if (n_com == 1 && p->command_not_found[0])
	{
		p->command_not_found[0] = 0;
		if (!ft_do_one_command(p))
		{
			ft_free_mem(p, n_com);
			return (0);
		}
	}
	else if (!ft_do_commands2(p, n_com))
	{
		ft_free_mem(p, n_com);
		return (0);
	}
	return (1);
}
