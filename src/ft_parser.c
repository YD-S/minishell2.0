/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:59:41 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/11 14:40:20 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_call_replace(char *prompt)
{
	char	*start;
	char	*end;
	char	*replace;
	int		i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '>' && prompt[i + 1] == '|')
		{
			replace = ">";
			start = prompt + i;
			end = prompt + i + 2;
			prompt = ft_replace(prompt, start, end, replace);
		}
		else if (prompt[i] == '<' && prompt[i + 1] == '>')
		{
			replace = "<";
			start = prompt + i;
			end = prompt + i + 2;
			prompt = ft_replace(prompt, start, end, replace);
		}
		i++;
	}
	return (prompt);
}

char	**ft_parser(char *prompt)
{
	char	**cmd;

	//prompt = ft_call_replace(prompt);
	cmd = ft_cmdtrim(prompt);
	print_charpp(cmd);
	if (prompt[ft_strlen(prompt) - 1] == ' ')
		cmd = ft_charpp_del_back(cmd);
	cmd = ft_expand_vars(cmd);
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
