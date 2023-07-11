/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:57:41 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/11 18:44:30 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **result, int index)
{
	while (index-- > 0)
		free(result[index]);
	free(result);
}

void	ft_executer(char **cmds, char **paths)
{
	int	i;

	i = ft_charpplen(cmds);
	ft_main(cmds, i, paths);
}


void	ft_main(char **argv, int argc, char **paths)
{
	t_pipex	p;
	int		i;
	int		pipes;
	int		cmd;
	int		args;

	pipes = ft_count_pipes(argv, argc - 1);
	i = 1;
	ft_reserve_memory(&p, pipes + 1, ft_count_max_args(argv, argc, i));
	ft_count_args(argv, argc, &p);
	i = 0;
	cmd = 0;
	while (i < argc)
	{
		args = 0;
		if (strncmp(argv[i], "<\0", 2) == 0)
		{
			p.infile[cmd] = argv[i + 1];
			i += 2;
		}
		else if (strncmp(argv[i], "<<\0", 3) == 0)
		{
			p.heredoc[cmd] = 1;
			p.infile[cmd] = ft_strjoin(argv[i + 1], "\n");
			i += 2;
		}
		else
		{
			p.infile[cmd] = 0;
		}
		p.paths[cmd] = ft_check_comm(paths, argv[i]);
		p.args[cmd][args] = argv[i];
		i++;
		while (i < argc && strncmp(argv[i], "|\0", 2) != 0)
		{
			if (strncmp(argv[i], ">\0", 2) == 0)
			{
				p.outfile[cmd] = argv[i + 1];
				i += 2;
			}
			else if (strncmp(argv[i], ">>\0", 3) == 0)
			{
				p.outfile[cmd] = argv[i + 1];
				p.outmode[cmd] = 1;
				i += 2;
			}
			if (i < argc && strncmp(argv[i], "|\0", 2) != 0)
				p.args[cmd][++args] = argv[i];
			else
				break ;
			i++;
		}
		i++;
		p.args[cmd][++args] = 0;
		cmd++;
	}
	ft_do_commands(&p, pipes + 1);
}
