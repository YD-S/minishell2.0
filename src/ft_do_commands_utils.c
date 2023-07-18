/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:22:03 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/18 17:44:53 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_pipex *p, int *file)
{
	char	*line;

	*file = open("aux.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, p->infile[p->i]) == 0)
		{
			free(line);
			break ;
		}
		write(*file, line, ft_strlen(line));
		free(line);
	}
	close(*file);
	*file = open("aux.txt", O_RDONLY);
	if (*file == -1)
		ft_write_error("file", strerror(errno), "aux.txt");
	if (dup2(*file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	unlink("aux.txt");
	close(*file);
}

int	ft_open_in_file(t_pipex *p, int fd[2])
{
	int	file;

	if (p->infile[p->i])
	{
		if (p->heredoc[p->i])
			ft_heredoc(p, &file);
		else
		{
			file = open(p->infile[p->i], O_RDONLY);
			if (file == -1)
			{
				ft_write_error("file", strerror(errno), p->infile[p->i]);
				return (0);
			}
			if (dup2(file, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(file);
		}
	}
	else
	{
		if (p->command_not_found[p->i - 1] == 0)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(fd[0]);
		}
		else
		{
			ft_printf("ASD2");
			close(fd[0]);
		}
	}
	return (1);
}

void	ft_open_out_file(t_pipex *p, int fd2[2])
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
		if (dup2(file, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(file);
	}
	else
	{
		if (dup2(fd2[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd2[1]);
	}
}

int	ft_open_first_file(t_pipex *p, int *file)
{
	if (p->heredoc[0])
		ft_heredoc(p, file);
	else
	{
		if (p->infile[0])
		{
			*file = open(p->infile[0], O_RDONLY);
			if (*file == -1)
			{
				ft_write_error("file", strerror(errno), p->infile[0]);
				return (0);
			}
			if (dup2(*file, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
	}
	return (1);
}

void	ft_open_first_out_file(t_pipex *p, int fd[2], int n_com)
{
	int	file;

	if (p->outfile[0])
	{
		if (p->outmode[p->i])
			file = open(p->outfile[p->i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file = open(p->outfile[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			ft_write_error("file", strerror(errno), p->outfile[p->i]);
		if (dup2(file, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(file);
	}
	else if (n_com > 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close (fd[1]);
	}
	else
	{
		close (fd[1]);
	}
}
