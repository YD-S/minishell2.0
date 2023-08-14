/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:58:28 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/14 18:00:58 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cpy(char *temp, char *new_str, t_count *count)
{
	new_str[count->j] = temp[count->i];
	count->i++;
	count->j++;
}

void	if_squote(char *temp, char *new_str, t_count *count)
{
	new_str[count->j] = temp[count->i];
	count->i++;
	while (temp[count->i] && temp[count->i] != '\'')
		do_cpy(temp, new_str, count);
}

void	if_dquote(char *temp, char *new_str, t_count *count)
{
	new_str[count->j] = temp[count->i];
	count->i++;
	while (temp[count->i] && temp[count->i] != '\"')
		do_cpy(temp, new_str, count);
}

void	free_var(t_envp *var)
{
	free(var->key);
	free(var->value);
	free(var);
}
