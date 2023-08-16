/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charppdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:10:55 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/16 16:59:58 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_charppdup(const char **str)
{
	char	**ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	ret = ft_calloc (sizeof(char *), (i + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
