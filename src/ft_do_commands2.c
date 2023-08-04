/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:47:17 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/04 15:30:45 by ysingh           ###   ########.fr       */
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

void	execute_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		execute_echo(cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		execute_export(cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		execute_cd(cmd);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		execute_pwd();
	if (ft_strcmp(cmd[0], "unset") == 0)
		execute_unset(cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		execute_exit();
	if (ft_strcmp(cmd[0], "env") == 0)
		execute_env(0);
}
