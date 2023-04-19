#include "minishell.h"

void ft_init_global(char **envp)
{
	t_envp	*env;

	while (*envp)
	{
		env = ft_calloc(1, sizeof(t_envp));
		env->key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		env->value = ft_substr(*envp, ft_strchr(*envp, '=') - *envp + 1, ft_strlen(*envp) - ft_strlen(env->key) - 1);
		ft_lstadd_back(&g_global.envp, ft_lstnew(env));
		envp++;
	}
	g_global.path = ft_get_env("PATH");
	g_global.exit_status = 0;
	g_global.heredoc_out = NULL;
	g_global.user = ft_get_env("USER");
}