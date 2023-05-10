
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

t_envp	*ft_get_node(char *str)
{
	t_list	*list;
	t_envp	*node;

	list = g_global.envp;
	while (list)
	{
		node = list->content;
		if (!ft_strcmp(str, node->key))
			return (node);
		list = list->next;
	}
	return (NULL);
}

char	*ft_get_var(char *cmd)
{
	char	*cpy;
	char	*aux;
	char	*aux2;
	t_envp	*var;
	int		i;
	int		j;

	i = 0;
	cpy = ft_strdup(cmd);
	if ((cmd[0] == SQ && cmd[ft_strlen(cmd) - 1] == SQ) || !ft_strchr(cpy, '$'))
		return (cpy);
	while (cpy[i])
	{
		aux = ft_strchr(cpy + i, '$');
		if (!aux)
			break ;
		j = ft_get_index(cpy, ft_strchr(cpy + i, '$'));
		if (ft_isspace(aux[1]) || aux[1] == '\0' || aux[1] == '$'
			|| aux[1] == '=' || aux[1] == '\"' || aux[1] == '\''
			|| aux[1] == '?' || aux[1] == '|')
		{
			i++;
			continue ;
		}
		aux2 = ft_strchrs(aux + 1, " $=\n\t?\'\"|");
		var = ft_get_node(ft_substr(cpy, ft_get_index(cpy, aux),
					ft_get_index(cpy, aux2) - ft_get_index(cpy, aux)));
		if (!var)
			cpy = ft_replace(cpy, aux, aux2, "");
		else
		{
			cpy = ft_replace(cpy, aux, aux2, var->value);
			i = j + (int)ft_strlen(var->value);
		}
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