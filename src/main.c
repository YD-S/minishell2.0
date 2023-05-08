
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	ft_init_global(envp);
	while (1)
	{
		line = ft_readline();
		add_history(line);
		ft_check_cmd(line);
		ft_parser(line);
	}
}

char	*ft_get_var(char *cmd)
{
	char	*cpy;
	char	*str;
	t_list	*list;
	t_envp	*var;
	char	*temp;

	printf("%s\n", cmd);
	cpy = ft_strdup(cmd);
	if (cmd[0] == SQ && cmd[ft_strlen(cmd) - 1] == SQ)
		return (cpy);
	list = g_global.envp;
	while (list)
	{
		var = list->content;
		str = cpy;
		while (ft_strnstr_perso(str, var->key, ft_strlen(str)))
		{
			temp = ft_strnstr_perso(str, var->key, ft_strlen(str));
			cpy = ft_replace(cpy, temp - str, (int)ft_strlen(var->key) + (temp
						- str) - 1, var->value);
			str = temp + ft_strlen(var->key);
		}
		list = list->next;
	}
	return (cpy);
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

void	ft_parser(char *prompt)
{
	char **cmd;

	cmd = ft_cmdtrim(prompt);
	for (int i = 0; i < ft_charpplen(cmd); i++)
		printf("before: %s\n", cmd[i]);
	cmd = ft_expand_vars(cmd);
	for (int i = 0; i < ft_charpplen(cmd); i++)
		printf("after: %s\n", cmd[i]);
}