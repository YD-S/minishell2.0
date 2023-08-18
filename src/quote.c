/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:29:40 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/18 15:03:13 by alvalope         ###   ########.fr       */
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
	char	*aux;
	int		j;
	int		len;

	len = ft_strclen(prompt, DQ, i + 1);
	aux = ft_calloc(len + 2, sizeof(char));
	j = 1;
	i++;
	aux[0] = DQ;
	while (prompt[i] != DQ)
	{
		aux[j] = prompt[i];
		if (prompt[i] == '\0')
			return (aux);
		i++;
		j++;
	}
	aux[j] = DQ;
	return (aux);
}

char	*ft_sq(char *prompt, int i)
{
	char	*aux;
	int		j;
	int		len;

	len = ft_strclen(prompt, SQ, i + 1);
	aux = ft_calloc(len + 2, sizeof(char));
	j = 1;
	i++;
	aux[0] = SQ;
	while (prompt[i] != SQ)
	{
		aux[j] = prompt[i];
		if (prompt[i] == '\0')
			return (aux);
		i++;
		j++;
	}
	aux[j] = SQ;
	return (aux);
}

int	wordlen_perso(char *prompt, int i)
{
	int	len;

	len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '<' && prompt[i] != '>'
		&& prompt[i] != '|')
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_noq(char *prompt, int i)
{
	char	*aux;
	int		j;
	int		len;

	len = wordlen_perso(prompt, i);
	aux = ft_calloc(len + 2, sizeof(char));
	j = 0;
	while (prompt[i] != ' ' && prompt[i] != '"'
		&& prompt[i] != '\'' && prompt[i] != '\0')
	{
		aux[j] = prompt[i];
		i++;
		j++;
	}
	return (aux);
}
