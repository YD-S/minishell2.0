/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:47:59 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/10 19:23:05 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_var(t_envp *var, char *arg)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	temp2 = ft_strjoin("$", temp);
	var->key = ft_strdup(temp2);
	var->value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg));
	free(temp);
	free(temp2);
}

void	get_new_var(t_envp var)
{
	t_envp	*new_var;

	new_var = ft_calloc(sizeof(t_envp), 1);
	new_var->key = var.key;
	new_var->value = var.value;
	ft_lstadd_back(&g_global.envp, ft_lstnew(new_var));
}

void	set_temp_path(void)
{
	char	*temp;

	temp = ft_get_env("$PATH");
	g_global.path = ft_split(temp, ':');
	free(temp);
}

int	check_pwd(void)
{
	if (search_var("$PWD") == 0 || ft_get_env("$PWD") == NULL)
	{
		ft_printf("Error: PWD not set\n");
		g_global.exit_status = 1;
		return (0);
	}
	return (1);
}

void	do_cd(char *path, int flag)
{
	if (flag == 1)
		ft_printf("%s\n", path);
	if (chdir(path) == -1)
		printg_status("Error: No such file or directory", 1);
	update_pwd();
	get_dir();
}
