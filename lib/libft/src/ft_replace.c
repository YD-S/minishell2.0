/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:35:56 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 18:57:38 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_index(char *str, char *index)
{
	int	i;

	i = 0;
	if (!index || !*index)
		return ((int)ft_strlen(str));
	while (str + i != index || !*(str + i))
	{
		i++;
	}
	return (i);
}

char	*ft_replace(char *str, char *start, char *end, char *replace)
{
	char	*left;
	char	*right;
	char	*final;

	left = ft_substr(str, 0, ft_get_index(str, start));
	right = ft_substr(str, ft_get_index(str, end), ft_strlen(str));
	final = ft_strjoin(left, replace);
	free(left);
	left = ft_strjoin(final, right);
	free(right);
	free(str);
	free(final);
	return (left);
}
