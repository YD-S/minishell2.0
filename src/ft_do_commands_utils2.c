/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:46:28 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/27 13:43:28 by alvalope         ###   ########.fr       */
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

void	ft_heredocs(t_pipex *p, int *file, char **delim)
{
	char	*line;
	int		delims;
	int		delim_count;
	int		i;

	p->i = p->i;
	delims = ft_charpplen(delim);
	*file = open("aux.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	delim_count = 0;
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, delim[delim_count]) == 0)
		{
			delim_count++;
		}
		if (ft_strcmp(line, delim[delims - 1]) == 0 && delim_count == delims)
		{
			free(line);
			break ;
		}
		i = 0;
		while (i < delims)
		{
			if (ft_strcmp(line, delim[i]) == 0)
				break ;
			i++;
		}
		if (delim_count == delims - 1 && i == delims)
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
