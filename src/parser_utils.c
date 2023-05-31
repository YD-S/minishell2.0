/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:07:42 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 19:08:13 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_red(char *prompt, int i)
{
	int		len;
	int		aux;
	char	*ret;

	len = 0;
	aux = i;
	while (prompt[aux] == '<')
	{
		len++;
		aux++;
	}
	ret = ft_substr(prompt, i, len);
	return (ret);
}

char	*ft_redback(char *prompt, int i)
{
	int		len;
	int		aux;
	char	*ret;

	len = 0;
	aux = i;
	while (prompt[aux] == '>')
	{
		len++;
		aux++;
	}
	ret = ft_substr(prompt, i, len);
	return (ret);
}

char	*ft_redpipe(char *prompt, int i)
{
	int		len;
	int		aux;
	char	*ret;

	len = 0;
	aux = i;
	while (prompt[aux] == '|')
	{
		len++;
		aux++;
	}
	ret = ft_substr(prompt, i, len);
	return (ret);
}
