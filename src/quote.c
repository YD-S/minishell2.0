/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:29:40 by ysingh            #+#    #+#             */
/*   Updated: 2023/07/22 21:06:09 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_quote(char *str)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen(str) - 1;
	ret = ft_calloc(len + 3, sizeof(char));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[len] = '"';
	ret[len + 1] = '"';
	free(str);
	return (ret);
}

char	*ft_dq(char *prompt, int i)
{
	int		len;
	char	*ret;

	len = ft_strclen(prompt, DQ, i + 1);
	ret = ft_substr(prompt, i, len + 2);
	return (ret);
}

char	*ft_sq(char *prompt, int i)
{
	int		len;
	char	*ret;

	len = ft_strclen(prompt, SQ, i + 1);
	ret = ft_substr(prompt, i, len + 2);
	return (ret);
}

int	wordlen_perso(char *prompt, int i)
{
	int	len;

	len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '<' && prompt[i] != '>' && prompt[i] != '|')
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_noq(char *prompt, int i)
{
	int		len;
	char	*ret;

	len = wordlen_perso(prompt, i);
	ret = ft_substr(prompt, i, len);
	return (ret);
}
