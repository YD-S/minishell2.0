/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:09:06 by ysingh            #+#    #+#             */
/*   Updated: 2023/06/01 16:52:49 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_validate_redirect(char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
			*i += 2;
		else
			*i += 1;
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
			*i += 2;
		else
			*i += 1;
	}
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		return (0);
	return (1);
}

int	ft_locate_firstpipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i += 1;
	if (str[i] == '|')
		return (0);
	return (1);
}

void	set_pipe_redirect(int *pipe, int *redirect, int flag)
{
	if (flag == 1)
	{
		*pipe = 1;
		*redirect = 0;
	}
	else if (flag == 2)
	{
		*redirect = 1;
		*pipe = 0;
	}
}

int	ft_validate(char *str)
{
	int	i;
	int	pipe;
	int	redirect;

	i = 0;
	pipe = 0;
	redirect = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (pipe == 1)
				return (0);
			set_pipe_redirect(&pipe, &redirect, 1);
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (redirect == 1 || !ft_validate_redirect(str, &i))
				return (0);
			set_pipe_redirect(&pipe, &redirect, 2);
		}
		i++;
	}
	return (1);
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
