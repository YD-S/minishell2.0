/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:58:54 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/18 15:08:33 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_global(char **envp)
{
	t_envp	*env;
	char	*temp;

	while (*envp)
	{
		env = ft_calloc(1, sizeof(t_envp));
		env->key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		env->value = ft_substr(*envp, ft_strchr(*envp, '=') - *envp + 1,
				ft_strlen(*envp) - ft_strlen(env->key) - 1);
		ft_lstadd_back(&g_global.envp, ft_lstnew(env));
		envp++;
	}
	ft_add_dollar();
	get_dir();
	temp = ft_get_env("$PATH");
	g_global.path = ft_split(temp, ':');
	g_global.exit_status = 0;
	g_global.heredoc_out = NULL;
	g_global.user = ft_get_env("$USER");
}

void	do_search_and_replace(char *key, char *value)
{
	search_and_replace(g_global.envp, key, value);
	if (ft_strcmp(key, "$PATH") == 0)
		set_temp_path();
}

void	search_and_replace(t_list *head, const char *key, const char *new_value)
{
	t_list	*current;
	t_envp	*env_node;

	current = head;
	while (current != NULL)
	{
		env_node = (t_envp *)current->content;
		if (ft_strcmp(env_node->key, key) == 0)
		{
			free(env_node->value);
			env_node->value = ft_strdup(new_value);
			return ;
		}
		current = current->next;
	}
}

void	ft_add_dollar(void)
{
	t_list	*tmp;
	t_envp	*env;
	char	*key_temp;

	tmp = g_global.envp;
	while (tmp)
	{
		env = tmp->content;
		key_temp = env->key;
		env->key = ft_strjoin("$", env->key);
		free(key_temp);
		tmp = tmp->next;
	}
}

char	*ft_get_env(char *key)
{
	t_list	*tmp;
	t_envp	*env;

	tmp = g_global.envp;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
