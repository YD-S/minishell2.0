/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:17 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/11 18:14:13 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "env") == 0)
		return (1);
	else
		return (0);
}

void	check_builtin(t_pipex *p, int i)
{
	if (ft_strcmp(p->args[i][0], "echo") == 0)
		execute_echo(p->args[i]);
	if (ft_strcmp(p->args[i][0], "export") == 0)
		execute_export(p->args[i]);
	if (ft_strcmp(p->args[i][0], "cd") == 0)
		execute_cd(p->args[i]);
	if (ft_strcmp(p->args[i][0], "pwd") == 0)
		execute_pwd();
	if (ft_strcmp(p->args[i][0], "unset") == 0)
		execute_unset(p->args[0]);
	if (ft_strcmp(p->args[i][0], "exit") == 0)
		execute_exit(p->args[0]);
	if (ft_strcmp(p->args[i][0], "env") == 0)
		execute_env(0);
}

void	execute_builtin2(t_pipex *p, int i, int fd[2])
{
	if (!p->outfl[i])
	{
		check_builtin(p, i);
		close(fd[0]);
	}
}

void	execute_builtin(t_pipex *p, int fd[2], int status, int i)
{
	int	pid;

	pipe(fd);
	if (p->outfl[i])
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_open_first_out_file(p, fd, 1);
			check_builtin(p, i);
			close(fd[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			while (waitpid(pid, &status, 0) != pid)
				;
			close(fd[1]);
			if (WIFEXITED(status))
				g_global.exit_status = WEXITSTATUS(status);
		}
	}
	execute_builtin2(p, i, fd);
}
