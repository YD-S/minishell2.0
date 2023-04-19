
#include "minishell.h"

int	quote_state(char c)
{
	static int	state;
	int			old_state;

	old_state = state;
	if (c == '"')
	{
		if (old_state == DQUOTE)
		{
			state = NOQUOTE;
			return (state);
		}
		else if (old_state == NOQUOTE)
			state = DQUOTE;
	}
	else if (c == '\'')
	{
		if (old_state == SQUOTE)
		{
			state = NOQUOTE;
			return (state);
		}
		else if (old_state == NOQUOTE)
			state = SQUOTE;
	}
	return (old_state);
}

void	ft_check_cmd(char *prompt)
{
	int	state;
	int	prev_state;
	int	i;

	state = NOQUOTE;
	prev_state = NOQUOTE;
	i = 0;
	while (prompt[i])
	{
		prev_state = state;
		state = quote_state(prompt[i]);
		i++;
	}
	if (state == NOQUOTE)
		printf("%c No quotes\n", prompt[i - 1]);
	else if (state == DQUOTE && prompt[i - 1] == '"' && prev_state == DQUOTE)
		printf("Double Quotes closed\n");
	else if (state == SQUOTE && prompt[i - 1] == '\'' && prev_state == SQUOTE)
		printf("Single Quotes closed\n");
	else
		printf("Quotes not closed\n");
}

char *ft_get_env(char *key)
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

void ft_print_lists(void)
{
	t_list	*tmp;
	t_envp	*env;

	tmp = g_global.envp;
	while (tmp)
	{
		env = tmp->content;
		printf("key: %s, value: %s\n", env->key, env->value);
		tmp = tmp->next;
	}
}
