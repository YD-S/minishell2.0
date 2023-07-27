/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:09:06 by ysingh            #+#    #+#             */
/*   Updated: 2023/07/26 16:34:13 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_vr(char *str, int *i)
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
	while (str[*i] == ' ' || str[*i] == '\t')
		*i += 1;
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
	else if (flag == 3)
	{
		*redirect = 0;
		*pipe = 0;
	}
}

int	ft_check_last_pipe(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i -= 1;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (0);
	return (1);
}

int	ft_validate(char *str)
{
	int				i;
	t_pipe_redirect	count;

	ft_init_count(&count, &i);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (count.pipe == 1 || (quote_state(str[i]) == NO
					&& !ft_locate_firstpipe(str)))
				return (0);
			set_pipe_redirect(&count.pipe, &count.re, 1);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (count.re == 1 && (quote_state(str[i]) == NO && !ft_vr(str, &i)))
				return (0);
			set_pipe_redirect(&count.pipe, &count.re, 2);
		}
		else if (str[i] != ' ' && str[i] != '\t' && str[i] != '|'
			&& str[i] != '<' && str[i] != '>')
			set_pipe_redirect(&count.pipe, &count.re, 3);
		i++;
	}
	return (ft_check_last_pipe(str));
}
