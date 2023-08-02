/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:43:44 by ysingh            #+#    #+#             */
/*   Updated: 2023/07/26 16:34:00 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchrs(const char *str, const char *chrs)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (chrs[j])
		{
			if (str[i] == chrs[j])
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	**ft_str_add_back(char **str, char *add)
{
	int		temp_len;
	int		len;
	char	**ret;

	len = ft_charpplen(str);
	temp_len = len;
	ret = ft_calloc(sizeof(char *), len + 2);
	while (len--)
		ret[len] = ft_strdup(str[len]);
	ret[temp_len] = ft_strdup(add);
	ft_charppfree(str);
	free(add);
	return (ret);
}
