/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:57:41 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/03 23:00:17 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executer(char **cmds, char **paths)
{
	int	i;

	i = ft_charpplen(cmds);
	ft_main(cmds, i, paths);
}

void	ft_separate_1st_cmd2(t_pipex *p, t_aux *auxs, char **argv)
{
	if (strncmp(argv[auxs->i], "<\0", 2) == 0)
	{
		p->infile[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
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
	if (argv[auxs->i])
		ft_check_outfile(p, auxs, argv);
}

void	ft_separate_1st_cmd(t_pipex *p, t_aux *auxs, char **argv, char **paths)
{
	char	*temp;

	auxs->args = 0;
	ft_separate_1st_cmd2(p, auxs, argv);
	if (argv[auxs->i] && strncmp(argv[auxs->i], "|\0", 2) != 0)
	{
		if (!get_builtin(argv[auxs->i]))
		{
			temp = ft_strdup(argv[auxs->i]);
			p->paths[auxs->cmd] = ft_check_comm(paths, temp, p, auxs->cmd);
			free(temp);
		}
		else
			p->paths[auxs->cmd] = ft_strdup(argv[auxs->i]);
		p->args[auxs->cmd][auxs->args] = ft_strdup(argv[auxs->i]);
	}
	auxs->i++;
}

int	ft_separate_cmds(t_pipex *p, t_aux *auxs, int argc, char **argv)
{
	int	file;

	file = -1;
	while (auxs->i < argc && strncmp(argv[auxs->i], "|\0", 2) != 0)
	{
		if (!ft_check_io_fl(p, auxs, argv, file))
		{
			p->args[auxs->cmd][++auxs->args] = ft_strdup(argv[auxs->i]);
			auxs->i++;
		}
	}
	return (1);
}

void	ft_main(char **argv, int argc, char **paths)
{
	t_pipex	p;
	t_aux	auxs;

	auxs.pipes = ft_count_pipes(argv, argc - 1);
	auxs.i = 0;
	ft_reserve_mem(&p, auxs.pipes + 1, ft_count_max_args(argv, argc, auxs.i));
	ft_count_args(argv, argc, &p);
	auxs.cmd = 0;
	while (auxs.i < argc)
	{
		ft_separate_1st_cmd(&p, &auxs, argv, paths);
		while (auxs.i < argc && strncmp(argv[auxs.i], "|\0", 2) != 0)
		{
			if (!ft_separate_cmds(&p, &auxs, argc, argv))
				break ;
		}
		auxs.i++;
		p.args[auxs.cmd][++auxs.args] = 0;
		auxs.cmd++;
	}
	if (p.paths[0])
		ft_do_commands(&p, auxs.pipes + 1);
	else if (p.heredoc[0])
		ft_do_heredoc(&p);
	ft_free_mem(&p, auxs.pipes + 1);
}
