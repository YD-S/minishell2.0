/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands_first_last.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:07:23 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/17 19:50:03 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_last_comm2(t_pipex *p, int fd[2])
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
	else
	{
		free_env();
		exit(EXIT_SUCCESS);
	}
	return (1);
}

void	ft_last_outfile(t_pipex *p)
{
	int	file;

	if (p->outfl[p->i])
	{
		if (p->outmode[p->i])
			file = open(p->outfl[p->i], O_WRONLY | O_APPEND);
		else
			file = open(p->outfl[p->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			ft_write_error("file", strerror(errno), p->outfl[p->i]);
		if (file)
		{
			if (dup2(file, STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(file);
		}
	}
}

int	ft_do_last_comm(t_pipex *p, int fd[2], pid_t pid)
{
	int		status;

	if (!get_builtin(p->args[p->i][0]))
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_last_outfile(p);
			if (!ft_do_last_comm2(p, fd))
				return (0);
		}
		else
		{
			while (waitpid(pid, &status, 0) != pid)
				;
			close(fd[1]);
			if (WIFEXITED(status))
				g_global.exit_status = 127;
		}
	}
	if (!ft_do_else(p, fd))
		return (0);
	return (1);
}

int	ft_do_first_comm2(t_pipex *p, int fd[2], int file, int n_com)
{
	int	status;

	ft_open_first_out_file(p, fd, n_com);
	close(fd[0]);
	if (p->infile[0])
		close(file);
	if (!get_builtin(p->args[0][0]))
	{
		if (execve(p->paths[0], p->args[0], g_global.env) == -1)
		{
			ft_write_error("cmd", strerror(errno), p->args[0][0]);
			g_global.exit_status = 127;
			free_env();
			return (0);
		}
	}
	else
	{
		status = 0;
		execute_builtin(p, fd, status, 0);
		free_env();
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int	ft_do_first_comm(t_pipex *p, int fd[2], int n_com)
{
	pid_t	pid;
	int		file;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (!ft_open_first_file(p, &file) || !ft_do_first_comm2(p, fd, file,
				n_com))
		{
			g_global.exit_status = 127;
			return (0);
		}
	}
	else
	{
		while (waitpid(pid, &status, 0) != pid)
			;
		close(fd[1]);
		if (WIFEXITED(status))
			g_global.exit_status = WEXITSTATUS(status);
	}
	return (1);
}
