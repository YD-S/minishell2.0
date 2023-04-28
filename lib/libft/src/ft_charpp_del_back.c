/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpp_del_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:57:22 by ysingh            #+#    #+#             */
/*   Updated: 2023/04/28 11:03:52 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_charpp_del_back(char **str)
{
	int		len;
	char	**ret;

	len = ft_charpplen(str) - 1;
	ret = ft_calloc(sizeof(char *), len+1);
	while (len--)
		ret[len] = str[len];
	free(str);
	return (ret);
}
