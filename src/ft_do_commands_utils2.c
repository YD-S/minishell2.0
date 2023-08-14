/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:46:28 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/11 14:47:17 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_pipex *p, int *file)
{
	char	*line;

	*file = open("aux.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline(FGREEN "> " FWHITE);
		if (!line)
			break ;
		if (ft_strcmp(line, p->infile[p->i]) == 0)
		{
			free(line);
			break ;
		}
		write(*file, line, ft_strlen(line));
		write(*file, "\n", 1);
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

void	ft_heredocs2(char **delim, int delim_count, int delims, int file)
{
	char	*line;

	while (1)
	{
		line = readline(FGREEN "> " FWHITE);
		if (!line)
			break ;
		if (ft_strcmp(line, delim[delim_count]) == 0)
			delim_count++;
		if (ft_strcmp(line, delim[delims - 1]) == 0 && delim_count == delims)
		{
			free(line);
			break ;
		}
		while (delims > 0)
		{
			if (ft_strcmp(line, delim[delims]) == 0)
				break ;
			delims--;
		}
		if (delim_count == delims - 1 && delims == 0)
			write(file, line, ft_strlen(line));
		free(line);
	}
}

void	ft_heredocs(t_pipex *p, int *file, char **delim)
{
	int	delims;
	int	delim_count;

	p->i = p->i;
	delims = ft_charpplen(delim);
	*file = open("aux.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	delim_count = 0;
	ft_heredocs2(delim, delim_count, delims, *file);
	close(*file);
	*file = open("aux.txt", O_RDONLY);
	if (*file == -1)
		ft_write_error("file", strerror(errno), "aux.txt");
	if (dup2(*file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	unlink("aux.txt");
	close(*file);
}

void	ft_do_heredoc(t_pipex *p)
{
	char	*line;

	while (1)
	{
		line = readline(FGREEN "> " FWHITE);
		if (!line)
			break ;
		if (ft_strcmp(line, p->infile[0]) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}
