/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:48:44 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/08 12:52:55 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("   ", 1);
		ft_printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	free_env(void)
{
	t_list	*list;
	t_list	*temp_list;
	t_envp	*node;
	t_envp	*temp;

	list = g_global.envp;
	while (list)
	{
		node = list->content;
		temp = node;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp_list = list;
		list = list->next;
		free(temp_list);
	}
	free(g_global.dir);
	ft_charppfree(g_global.path);
	ft_charppfree(g_global.env);
}

void	handle_eof(char *line)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("exit", 1);
	ft_putstr_fd("\n", 1);
	free(line);
	free_env();
	exit(0);
}
