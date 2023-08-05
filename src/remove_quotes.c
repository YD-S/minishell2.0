/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:01:30 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/06 00:03:23 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **str)
{
	size_t	length;

	length = strlen(*str);
	if (length >= 2 && ((*str)[0] == '"' || (*str)[0] == '\'') && (*str)[length
			- 1] == (*str)[0])
	{
		ft_memmove(*str, *str + 1, length - 2);
		(*str)[length - 2] = '\0';
	}
}

void	init_all_things(t_count *count)
{
	count->i = 0;
	count->j = 0;
}

void	remove_quotes_in_array(char **str_array)
{
	int	i;

	i = 0;
	while (i < ft_charpplen(str_array))
	{
		remove_quotes(&str_array[i]);
		i++;
	}
}
