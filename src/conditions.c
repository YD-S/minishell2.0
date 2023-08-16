/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:06:26 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/16 19:07:29 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	condition(t_master mas)
{
	return (mas.strs.aux[1] == '\0' || mas.strs.aux[1] == '$'
		|| mas.strs.aux[1] == '=' || mas.strs.aux[1] == '\"'
		|| mas.strs.aux[1] == '\'' || mas.strs.aux[1] == '?'
		|| mas.strs.aux[1] == '|');
}

int	condition2(char *cmd, t_master mas)
{
	return ((cmd[ft_strlen(cmd) - 1] == SQ) || !ft_strchr(mas.strs.cpy, '$'));
}

int	condition3(t_master mas)
{
	return (mas.strs.cpy[mas.count.i] == '$' && mas.strs.cpy[mas.count.i
			+ 1] == '?');
}

void	if_dollar_int(t_master *mas)
{
	char	*temp;

	temp = ft_itoa(g_global.exit_status);
	mas->strs.cpy = ft_replace(mas->strs.cpy, mas->strs.cpy + mas->count.i,
			mas->strs.cpy + mas->count.i + 2, temp);
	mas->count.i += (int)ft_strlen(temp);
	free(temp);
}

void	init_all(t_master *mas, char *cmd)
{
	mas->count.i = 0;
	mas->strs.cpy = ft_strdup(cmd);
}
