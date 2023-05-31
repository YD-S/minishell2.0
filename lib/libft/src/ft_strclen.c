/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:53:19 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 18:58:20 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strclen(char *str, char c, int start)
{
	int	ret;

	ret = 0;
	while (str[start] && str[start] != c)
	{
		ret++;
		start++;
	}
	return (ret);
}
