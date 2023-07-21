/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:01:30 by ysingh            #+#    #+#             */
/*   Updated: 2023/07/21 13:05:23 by ysingh           ###   ########.fr       */
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
		memmove(*str, *str + 1, length - 2);
		(*str)[length - 2] = '\0';
	}
}

void	init_all_things(t_count *count)
{
	count->i = 0;
	count->j = 0;
}

void	remove_nested_quotes(char **str)
{
	char	*src;
	char	*dest;
	t_count	count;

	init_all_things(&count);
	src = *str;
	dest = *str;
	while (*src != '\0')
	{
		if (*src == DQ && (*(src - 1) != '\\' || (src - 2 >= *str && *(src
						- 2) == '\\')) && !count.i)
			count.j = !count.j;
		else if (*src == SQ && (*(src - 1) != '\\' || (src - 2 >= *str
					&& *(src - 2) == '\\')) && !count.j)
			count.i = !count.i;
		if ((*src != DQ && !count.j) || (*src != SQ
				&& !count.i))
		{
			*dest = *src;
			dest++;
		}
		src++;
	}
	*dest = '\0';
}

void	remove_quotes_in_array(char **str_array)
{
	int	i;

	i = 0;
	while (i < ft_charpplen(str_array))
	{
		remove_quotes(&str_array[i]);
		remove_nested_quotes(&str_array[i]);
		i++;
	}
}
