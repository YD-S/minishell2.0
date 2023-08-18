/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:12:37 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/17 16:08:15 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_join(char *comm, char *paths)
{
	char	*aux;
	char	*aux2;

	aux = ft_strjoin(paths, "/");
	aux2 = ft_strjoin(aux, comm);
	free(aux);
	return (aux2);
}

char	*ft_check_comm(char **paths, char *comm, t_pipex *p, int cmd)
{
	int		i;
	char	*aux2;

	i = 0;
	if (!paths)
	{
		ft_printf("%s: No such file or directory\n", comm);
		g_global.exit_status = 127;
		return (NULL);
	}
	while (paths[i] != 0)
	{
		if (comm[0] != '/')
			aux2 = do_join(comm, paths[i]);
		else
			aux2 = ft_strjoin("", comm);
		if (access(aux2, F_OK) != -1 && access(aux2, X_OK) != -1)
			return (aux2);
		free(aux2);
		i++;
	}
	p->command_not_found[cmd] = 1;
	return (comm);
}

int	ft_count_pipes(char *argv[], int n)
{
	int	pipes;

	pipes = 0;
	while (n > 0)
	{
		if (strncmp(argv[n], "|\0", 2) == 0)
			pipes++;
		n--;
	}
	return (pipes);
}

int	ft_count_max_args(char *argv[], int n, int i)
{
	int	max_args;
	int	args;

	max_args = 0;
	args = 0;
	while (i < n)
	{
		if (strncmp(argv[i], "|\0", 2) == 0)
			args = 0;
		else if (strncmp(argv[i], "<\0", 2) == 0 || strncmp(argv[i], "<<\0",
				2) == 0)
			i += 1;
		else if (strncmp(argv[i], ">\0", 2) == 0 || strncmp(argv[i], ">>\0",
				2) == 0)
			i += 1;
		else
		{
			args++;
			if (args > max_args)
				max_args = args;
		}
		i++;
	}
	return (max_args);
}

void	ft_count_args(char *argv[], int n, t_pipex *p)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 1;
	while (i < n)
	{
		if (strncmp(argv[i], "|\0", 2) == 0)
			pipes++;
		else if (strncmp(argv[i], "<\0", 2) == 0 || strncmp(argv[i], "<<\0",
				2) == 0)
			i += 1;
		else if (strncmp(argv[i], ">\0", 2) == 0 || strncmp(argv[i], ">>\0",
				2) == 0)
			i += 1;
		else
			p->n_args[pipes]++;
		i++;
	}
}
