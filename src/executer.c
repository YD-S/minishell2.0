/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:57:41 by alvalope          #+#    #+#             */
/*   Updated: 2023/08/16 16:56:55 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executer(char **cmds, char **paths)
{
	int		i;
	t_aux	auxs;

	auxs.i = 0;
	i = ft_charpplen(cmds);
	auxs.pipes = ft_count_pipes(cmds, i - 1);
	ft_main(cmds, i, paths, auxs);
}

int	ft_separate_1st_cmd2(t_pipex *p, t_aux *auxs, char **argv)
{
	if (strncmp(argv[auxs->i], "<\0", 2) == 0)
	{
		p->infile[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		auxs->i += 2;
		return (1);
	}
	else if (strncmp(argv[auxs->i], "<<\0", 3) == 0)
	{
		p->heredoc[auxs->cmd] = 1;
		p->infile[auxs->cmd] = ft_strdup(argv[auxs->i + 1]);
		auxs->i += 2;
		return (1);
	}
	if (argv[auxs->i])
		return (ft_check_outfile(p, auxs, argv));
	return (0);
}

void	ft_separate_1st_cmd(t_pipex *p, t_aux *auxs, char **argv, char **paths)
{
	char	*temp;

	auxs->args = 0;
	while (argv[auxs->i] && ft_separate_1st_cmd2(p, auxs, argv))
		;
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

void	ft_main(char **argv, int argc, char **paths, t_aux auxs)
{
	t_pipex	p;

	do_call(&p, auxs, argv, argc);
	auxs.cmd = 0;
	while (auxs.i < argc)
	{
		ft_separate_1st_cmd(&p, &auxs, argv, paths);
		while (auxs.i < argc && ft_strncmp(argv[auxs.i], "|\0", 2) != 0)
			ft_separate_cmds(&p, &auxs, argc, argv);
		auxs.i++;
		p.args[auxs.cmd][++auxs.args] = 0;
		auxs.cmd++;
	}
	*p.args = remove_quotes_in_array(*p.args);
	if (p.paths[0])
	{
		if (!ft_do_commands(&p, auxs.pipes + 1))
			exit(EXIT_FAILURE);
	}
	else if (p.heredoc[0])
		ft_do_heredoc(&p);
	ft_free_mem(&p, auxs.pipes + 1);
}
