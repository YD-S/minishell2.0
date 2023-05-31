/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:06:19 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 19:08:39 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
