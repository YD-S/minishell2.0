/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:07:42 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/06 00:39:27 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_red(char *prompt, int i)
{
	int		len;
	int		aux;
	char	*ret;

	len = 0;
	aux = i;
	while (prompt[aux] == '<')
	{
		len++;
		aux++;
	}
	ret = ft_substr(prompt, i, len);
	return (ret);
}

char	*ft_redback(char *prompt, int i)
{
	int		len;
	int		aux;
	char	*ret;

	len = 0;
	aux = i;
	while (prompt[aux] == '>')
	{
		len++;
		aux++;
	}
	ret = ft_substr(prompt, i, len);
	return (ret);
}

char	*ft_redpipe(char *prompt, int i)
{
	int		len;
	int		aux;
	char	*ret;

	len = 0;
	aux = i;
	while (prompt[aux] == '|')
	{
		len++;
		aux++;
	}
	ret = ft_substr(prompt, i, len);
	return (ret);
}

void	ft_init_count(t_pipe_redirect *count, int *i)
{
	count->pipe = 0;
	count->re = 0;
	*i = 0;
}

int	ft_check_cmd(char *prompt)
{
	int	state;
	int	i;

	__qs('\0', 1);
	state = NO;
	i = 0;
	while (prompt[i])
	{
		state = quote_state(prompt[i]);
		i++;
	}
	if (state != NO && state != SQC && state != DQC)
	{
		ft_printf("Quote Error\n");
		return (0);
	}
	__qs('\0', 1);
	if (!ft_locate_firstpipe(prompt))
		return (0);
	return (ft_validate(prompt));
}
