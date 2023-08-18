/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpp_del_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:57:22 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 18:56:31 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_charpp_del_back(char **str)
{
	char	**ret;
	int		len;
	int		i;

	len = ft_charpplen(str);
	ret = ft_calloc(len, sizeof(char *));
	i = 0;
	while (i < len - 1)
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ft_charppfree(str);
	return (ret);
}
