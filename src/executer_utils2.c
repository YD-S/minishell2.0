/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:49:40 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/03 22:26:54 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **result, int index)
{
	while (index-- > 0)
		free(result[index]);
	free(result);
}

void	ft_free_mem(t_pipex *p, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd)
	{
		ft_charppfree((p->args[i]));
		if (cmd > 1 || (cmd == 1 && !p->command_not_found[0]))
			free(p->paths[i]);
		free(p->infile[i]);
		free(p->outfl[i]);
		i++;
	}
	free(p->paths);
	free(p->infile);
	free(p->outfl);
	free(p->n_args);
	free(p->heredoc);
	free(p->outmode);
	free(p->args);
	free(p->command_not_found);
}

void	ft_write_error(char *type, char *error, char *obj)
{
	if (ft_strcmp(type, "cmd") == 0)
	{
		write(2, "bash: ", 6);
		write(2, obj, ft_strlen(obj));
		write(2, ": command not found\n", 21);
	}
	else if (ft_strcmp(type, "file") == 0)
	{
		write(2, "bash: ", 6);
		write(2, obj, ft_strlen(obj));
		write(2, ": ", 2);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
}

void	ft_check_outfile(t_pipex *p, t_aux *auxs, char **argv)
{
	if (strncmp(argv[auxs->i], ">\0", 2) == 0)
	{
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		auxs->i += 2;
	}
	else if (strncmp(argv[auxs->i], ">>\0", 3) == 0)
	{
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		p->outmode[auxs->cmd] = 1;
		auxs->i += 2;
	}
}

int	ft_check_io_fl(t_pipex *p, t_aux *auxs, char **argv, int file)
{
	if (strncmp(argv[auxs->i], ">\0", 2) == 0)
	{
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		file = open(p->outfl[auxs->cmd], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(file);
	}
	else if (strncmp(argv[auxs->i], ">>\0", 3) == 0)
	{
		p->outfl[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		p->outmode[auxs->cmd] = 1;
		file = open(p->outfl[auxs->cmd], O_WRONLY | O_APPEND);
		close(file);
	}
	else if (strncmp(argv[auxs->i], "<\0", 2) == 0)
		p->infile[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
	else if (strncmp(argv[auxs->i], "<<\0", 3) == 0)
	{
		p->heredoc[auxs->cmd] = 1;
		p->infile[auxs->cmd] = ft_strjoin(argv[auxs->i + 1], "\n");
	}
	else
		return (0);
	auxs->i += 2;
	return (1);
}
