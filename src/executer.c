/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:57:41 by alvalope          #+#    #+#             */
/*   Updated: 2023/07/12 20:58:07 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executer(char **cmds)
{
	int	i;

	i = ft_charpplen(cmds);
	ft_main(cmds, i);
}

void	ft_separate_cmd(t_pipex *p, t_aux *auxs, char **argv, char **paths)
{
	auxs->args = 0;
	if (strncmp(argv[auxs->i], "<\0", 2) == 0)
	{
		p->infile[auxs->cmd] = argv[auxs->i + 1];
		auxs->i += 2;
	}
	else if (strncmp(argv[auxs->i], "<<\0", 3) == 0)
	{
		p->heredoc[auxs->cmd] = 1;
		p->infile[auxs->cmd] = ft_strjoin(argv[auxs->i + 1], "\n");
		auxs->i += 2;
	}
	else
	{
		p->infile[auxs->cmd] = 0;
	}
	p->paths[auxs->cmd] = ft_check_comm(paths, argv[auxs->i]);
	p->args[auxs->cmd][auxs->args] = argv[auxs->i];
	auxs->i++;
}

int	ft_separate_cmd2(t_pipex *p, t_aux *auxs, int argc, char **argv)
{
	if (strncmp(argv[auxs->i], ">\0", 2) == 0)
	{
		p->outfile[auxs->cmd] = argv[auxs->i + 1];
		auxs->i += 2;
	}
	else if (strncmp(argv[auxs->i], ">>\0", 3) == 0)
	{
		p->outfile[auxs->cmd] = argv[auxs->i + 1];
		p->outmode[auxs->cmd] = 1;
		auxs->i += 2;
	}
	if (auxs->i < argc && strncmp(argv[auxs->i], "|\0", 2) != 0)
		p->args[auxs->cmd][++auxs->args] = argv[auxs->i];
	else
		return (0);
	auxs->i++;
	return (1);
}

void	ft_main(char **argv, int argc)
{
	t_pipex	p;
	t_aux	auxs;

	auxs.pipes = ft_count_pipes(argv, argc - 1);
	auxs.i = 1;
	ft_reserve_mem(&p, auxs.pipes + 1, ft_count_max_args(argv, argc, auxs.i));
	ft_count_args(argv, argc, &p);
	auxs.i = 0;
	auxs.cmd = 0;
	while (auxs.i < argc)
	{
		ft_separate_cmd(&p, &auxs, argv, g_global.path);
		while (auxs.i < argc && strncmp(argv[auxs.i], "|\0", 2) != 0)
		{
			if (!ft_separate_cmd2(&p, &auxs, argc, argv))
				break ;
		}
		auxs.i++;
		p.args[auxs.cmd][++auxs.args] = 0;
		auxs.cmd++;
	}
	ft_do_commands(&p, auxs.pipes + 1);
	ft_charppfree(argv);
	ft_free_mem(&p, auxs.pipes + 1);
}
