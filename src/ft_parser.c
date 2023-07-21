/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:59:41 by ysingh            #+#    #+#             */
/*   Updated: 2023/07/21 13:59:20 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_parser(char *prompt)
{
	char	**cmd;

	cmd = ft_cmdtrim(prompt);
	if (prompt[ft_strlen(prompt) - 1] == ' ')
		cmd = ft_charpp_del_back(cmd);
	cmd = ft_expand_vars(cmd);
	remove_quotes_in_array(cmd);
	free(prompt);
	return (cmd);
}

char	*ft_call_noq(char *prompt, int *i)
{
	char	*aux;

	aux = ft_noq(prompt, *i);
	*i += strlen(aux);
	return (aux);
}

char	**ft_cmdtrim(char *prompt)
{
	char	**ret;
	char	*aux;
	int		i;

	i = 0;
	ret = NULL;
	while (i < (int)ft_strlen(prompt))
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == DQ)
			aux = ft_call_dq(prompt, &i);
		else if (prompt[i] == SQ)
			aux = ft_call_sq(prompt, &i);
		else if (prompt[i] == '<')
			aux = ft_call_red(prompt, &i);
		else if (prompt[i] == '>')
			aux = ft_call_redback(prompt, &i);
		else if (prompt[i] == '|')
			aux = ft_call_pipe(prompt, &i);
		else
			aux = ft_call_noq(prompt, &i);
		ret = ft_str_add_back(ret, aux);
	}
	return (ret);
}

char	**ft_expand_vars(char **cmd)
{
	char	**ret;
	int		i;

	i = -1;
	ret = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
		ret = ft_str_add_back(ret, ft_get_var(cmd[i]));
	ft_charppfree(cmd);
	return (ret);
}

int	ft_check_cmd(char *prompt)
{
	int	state;
	int	i;

	__qs('\0', 1);
	state = NO;
	i = 0;
	while (prompt[i])
	{
		state = quote_state(prompt[i]);
		i++;
	}
	if (state != NO && state != SQC && state != DQC)
	{
		ft_printf("Quote Error\n");
		return (0);
	}
	__qs('\0', 1);
	if (!ft_locate_firstpipe(prompt))
		return (0);
	return (ft_validate(prompt));
}
