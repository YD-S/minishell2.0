/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:35:56 by ysingh            #+#    #+#             */
/*   Updated: 2023/04/19 22:35:56 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_replace(char *str, int start, int end, char *replace)
{
	char *left;
	char *right;
	char *final;

	left = ft_substr(str, 0, start);
	right = ft_substr(str, end + 1, ft_strlen(str) - (end + 1));
	final = ft_strjoin(left, replace);
	free(left);
	left = ft_strjoin(final, right);
	free(right);
	free(str);
	return (left);
}
