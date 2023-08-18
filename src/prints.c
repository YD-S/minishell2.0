/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:06:57 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/17 17:02:57 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, char *line)
{
	free(line);
	ft_putstr_fd(str, 2);
	g_global.exit_status = 258;
}

char	*ft_readline(void)
{
	char	*line;

	ft_printf(FBLUE "%s", g_global.dir);
	ft_printf(FYELLOW "@");
	line = readline(FGREEN "minishell> " FWHITE);
	if (!line)
		handle_eof(line);
	else if (line[0])
		add_history(line);
	return (line);
}

void	printg_status(char *error, int status)
{
	ft_printf("%s\n", error);
	g_global.exit_status = status;
}
