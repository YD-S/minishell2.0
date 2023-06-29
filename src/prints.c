/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:06:57 by ysingh            #+#    #+#             */
/*   Updated: 2023/06/29 14:21:20 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_error(char *str, char *line)
{
	free(line);
	ft_putstr_fd(str, 2);
}

char	*ft_readline(void)
{
	char	*line;

	if (ft_strcmp(g_global.user, "root") == 0 || ft_strcmp(g_global.user,
			"admin") == 0)
		line = readline(FRED "minishell$ " NONE);
	else
		line = readline(FGREEN "minishell> " NONE);
	if (!line)
		 handle_eof();
	return (line);
}
