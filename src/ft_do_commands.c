/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:22:03 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/26 14:09:50 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_command(t_pipex *p, int fd[2], int fd2[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		ft_open_out_file(p, fd2);
		if (!get_builtin(p->args[p->i][0]))
		{
			if (ft_open_in_file(p, fd))
			{
				if (execve(p->paths[p->i], p->args[p->i], 0) == -1)
				{
					ft_write_error("cmd", strerror(errno), p->args[p->i][0]);
					return (g_global.exit_status = 127, 0);
				}
			}
			else
				return (g_global.exit_status = 127, 0);
		}
		else
			execute_builtin(p->args[p->i]);
		return (g_global.exit_status = 0, 1);
	}
	else
	{
		while (waitpid(pid, NULL, 0) != pid)
			;
		ft_printf("BBB");
		close(fd2[1]);
		return (g_global.exit_status = 0, 1);
	}
}

int	ft_do_last_comm(t_pipex *p, int fd[2])
{
	int	file;

	if (p->outfile[p->i])
	{
		if (p->outmode[p->i])
			file = open(p->outfile[p->i], O_WRONLY | O_APPEND);
		else
			file = open(p->outfile[p->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			ft_write_error("file", strerror(errno), p->outfile[p->i]);
		if (file)
		{
			if (dup2(file, STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(file);
		}
	}
	if (!get_builtin(p->args[p->i][0]))
	{
		ft_open_in_file(p, fd);
		if (execve(p->paths[p->i], p->args[p->i], 0) == -1)
		{
			ft_write_error("cmd", strerror(errno), p->args[p->i][0]);
			return (g_global.exit_status = 127, 0);
		}
	}
	else
		execute_builtin(p->args[p->i]);
	return (g_global.exit_status = 0, 1);
}

int	ft_do_first_comm(t_pipex *p, int fd[2], int n_com)
{
	pid_t	pid;
	int		file;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		//ft_printf("pid: %d\n", pid);
		if (ft_open_first_file(p, &file))
		{
			ft_open_first_out_file(p, fd, n_com);
			close(fd[0]);
			if (p->infile[0])
				close(file);
			if (!get_builtin(p->args[0][0]))
			{
				if (execve(p->paths[0], p->args[0], 0) == -1)
				{
					ft_write_error("cmd", strerror(errno), p->args[0][0]);
					return (g_global.exit_status = 127, 0);
				}
			}
			else
				execute_builtin(p->args[0]);
		}
		else
			return (g_global.exit_status = 127, 0);
	}
	else
	{
		//ft_printf("pid: %d\n", pid);
		while (waitpid(pid, NULL, 0) != pid)
			;
		//ft_printf("AAA%d-%d-%d/", pid, fd[0], fd[1]);
		close(fd[1]);
	}
	return (g_global.exit_status = 0, 1);
}

int	ft_do_commands(t_pipex *p, int n_com)
{
	int	fd[2];
	int	fd2[2];

	pipe(fd);
	if (!ft_do_first_comm(p, fd, n_com))
		exit(EXIT_FAILURE);
	p->i = 1;
	while (p->i < n_com - 1)
	{
		pipe(fd2);
		if (!ft_do_command(p, fd, fd2))
			exit(EXIT_FAILURE);
		fd[0] = fd2[0];
		p->i++;
	}
	if (n_com > 1)
	{
		if (!ft_do_last_comm(p, fd))
			exit(EXIT_FAILURE);
	}
	return (1);
}
