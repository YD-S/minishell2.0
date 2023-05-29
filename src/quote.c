/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:29:40 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/09 20:08:41 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_quote(char *str)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen(str) - 1;
	ret = ft_calloc(len + 3, sizeof(char));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[len] = '"';
	ret[len + 1] = '"';
	free(str);
	return (ret);
}

char	*ft_dq(char *prompt, int i)
{
	int		len;
	char	*ret;

	len = ft_strclen(prompt, DQ, i + 1);
	ret = ft_substr(prompt, i, len + 2);
	return (ret);
}

char	*ft_sq(char *prompt, int i)
{
	int		len;
	char	*ret;

	len = ft_strclen(prompt, SQ, i + 1);
	ret = ft_substr(prompt, i, len + 2);
	return (ret);
}

int	wordlen(char *prompt, int i)
{
	int	len;

	len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != SQ && prompt[i] != DQ)
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_noq(char *prompt, int i)
{
	int		len;
	char	*ret;

	len = wordlen(prompt, i);
	ret = ft_substr(prompt, i, len);
	return (ret);
}

static int	__qs_dq(int old_state)
{
	if (old_state == SQI || old_state == SQO)
		return (SQI);
	else if (old_state == DQI || old_state == DQO)
		return (DQC);
	return (DQO);
}

static int	__qs_sq(int old_state)
{
	if (old_state == DQI || old_state == DQO)
		return (DQI);
	else if (old_state == SQO || old_state == SQI)
		return (SQC);
	return (SQO);
}

static int	__qs_char(int old_state)
{
	if (old_state == DQO || old_state == DQI)
		return (DQI);
	else if (old_state == SQO || old_state == SQI)
		return (SQI);
	else if (old_state == DQC || old_state == SQC)
		return (NO);
	return (NO);
}

int	__qs(char c, int reset)
{
	static int	state;
	int			old_state;

	if (reset)
	{
		state = NO;
		return (0);
	}
	old_state = state;
	if (c == DQ)
		state = __qs_dq(old_state);
	else if (c == SQ)
		state = __qs_sq(old_state);
	else
		state = __qs_char(old_state);
	return (state);
}

int	quote_state(char c)
{
	return (__qs(c, 0));
}