/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:01:30 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/16 16:59:08 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all_things(t_count *count)
{
	count->i = 0;
	count->j = 0;
}

void	remove_quotes(char **str)
{
	t_count	count;
	char	*temp;

	init_all_things(&count);
	temp = ft_strdup(*str);
	while (temp[count.i])
	{
		if (temp[count.i] == '\'' && count.j % 2 == 0)
			count.j++;
		else if (temp[count.i] == '\'' && count.j % 2 != 0)
			count.j--;
		if (temp[count.i] == '\"' && count.j % 2 == 0)
			count.j++;
		else if (temp[count.i] == '\"' && count.j % 2 != 0)
			count.j--;
		count.i++;
	}
	if (count.j != 0)
		*str = ft_strdup(temp);
	free(temp);
}

void	remove_nested_quotes(char **str)
{
	char	*temp;
	char	*new_str;
	t_count	count;

	init_all_things(&count);
	temp = ft_strdup(*str);
	new_str = malloc(sizeof(char) * (ft_strlen(temp) + 1));
	while (temp[count.i])
	{
		if (temp[count.i] == '\"')
			if_dquote(temp, new_str, &count);
		if (temp[count.i] == '\'')
			if_squote(temp, new_str, &count);
		if (temp[count.i] == '\"' || temp[count.i] == '\'')
			count.i++;
		else
			do_cpy(temp, new_str, &count);
	}
	new_str[count.j] = '\0';
	free(*str);
	*str = ft_strdup(new_str);
	free(temp);
	free(new_str);
}

char	**remove_quotes_in_array(char **str_array)
{
	int		i;
	char	**temp;

	temp = ft_charppdup((const char **)str_array);
	i = 0;
	while (i < ft_charpplen(temp))
	{
		remove_nested_quotes(&temp[i]);
		i++;
	}
	ft_charppfree(str_array);
	return (temp);
}
