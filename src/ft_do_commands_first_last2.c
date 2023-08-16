/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands_first_last2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:09:35 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/16 10:56:55 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_else(t_pipex *p, int fd[2])
{
	int	status;

	if (get_builtin(p->args[p->i][0]))
	{
		status = 1;
		execute_builtin(p, fd, status, p->i);
	}
	return (1);
}
