/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:06:57 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 19:09:39 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printcustomascii(void)
{
	printf("\033[31m   __  ____      _ __       ____\n");
	printf("\033[32m  /  |/  (_)__  (_) /  ___ / / /\n");
	printf("\033[33m / /|_/ / / _ \\/ / _ \\/ -_) / / \n");
	printf("\033[34m/_/  /_/_/_//_/_/_//_/\\__/_/_/  \n");
	printf("\033[0m                                \n");
}

char	*ft_readline(void)
{
	char	*line;

	if (ft_strcmp(g_global.user, "root") == 0 || ft_strcmp(g_global.user,
			"admin") == 0)
		line = readline(FRED "minishell$ " NONE);
	else
		line = readline(FGREEN "minishell> " NONE);
	return (line);
}
