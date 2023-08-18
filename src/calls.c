/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:09 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 19:51:36 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_call_dq(char *prompt, int *i)
{
	char	*aux;

	aux = ft_dq(prompt, *i);
	*i += ft_strlen(aux);
	return (aux);
}

char	*ft_call_sq(char *prompt, int *i)
{
	char	*aux;

	aux = ft_sq(prompt, *i);
	*i += ft_strlen(aux);
	return (aux);
}

char	*ft_call_red(char *prompt, int *i)
{
	char	*aux;

	aux = ft_red(prompt, *i);
	*i += strlen(aux);
	return (aux);
}

char	*ft_call_redback(char *prompt, int *i)
{
	char	*aux;

	aux = ft_redback(prompt, *i);
	*i += strlen(aux);
	return (aux);
}

char	*ft_call_pipe(char *prompt, int *i)
{
	char	*aux;

	aux = ft_redpipe(prompt, *i);
	*i += strlen(aux);
	return (aux);
}
