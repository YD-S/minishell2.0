/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:17 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/10 11:14:52 by alvalope         ###   ########.fr       */
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

void	check_builtin(t_pipex *p)
{
	if (ft_strcmp(p->args[0][0], "echo") == 0)
		execute_echo(p->args[0]);
	if (ft_strcmp(p->args[0][0], "export") == 0)
		execute_export(p->args[0]);
	if (ft_strcmp(p->args[0][0], "cd") == 0)
		execute_cd(p->args[0]);
	if (ft_strcmp(p->args[0][0], "pwd") == 0)
		execute_pwd();
	if (ft_strcmp(p->args[0][0], "unset") == 0)
		execute_unset(p->args[0]);
	if (ft_strcmp(p->args[0][0], "exit") == 0)
		execute_exit(p->args[0]);
	if (ft_strcmp(p->args[0][0], "env") == 0)
		execute_env(0);
}

void	execute_builtin(t_pipex *p, int fd[2])
{
	int	pid;

	if (p->outfl[0])
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			ft_open_first_out_file(p, fd, 1);
			check_builtin(p);
			close(fd[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			while (waitpid(pid, NULL, 0) != pid)
				;
			close(fd[1]);
		}
	}
	else
		check_builtin(p);
}
