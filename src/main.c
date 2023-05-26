
#include "minishell.h"

static void	printcustomascii(void)
{
	printf("\033[31m   __  ____      _ __       ____\n");
	printf("\033[32m  /  |/  (_)__  (_) /  ___ / / /\n");
	printf("\033[33m / /|_/ / / _ \\/ / _ \\/ -_) / / \n");
	printf("\033[34m/_/  /_/_/_//_/_/_//_/\\__/_/_/  \n");
	printf("\033[0m                                \n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	printcustomascii();
	ft_init_global(envp);
	while (1)
	{
		line = ft_readline();
		add_history(line);
		ft_check_cmd(line);
		ft_parser(line);
		free(line);
        system("leaks -q Minishell");
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
			return (free(str), node);
		list = list->next;
	}
	return (free(str), NULL);
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
		return (ft_printf("Returned\n"), cpy);
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
   // char    *str;
	int		i;

	i = -1;
	ret = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[++i]){
        //str = ft_get_var(cmd[i]);
		ret = ft_str_add_back(ret, ft_get_var(cmd[i]));
        //free(str);
    }
	ft_charppfree(cmd);
	return (ret);
}

void	ft_parser(char *prompt)
{
	char	**cmd;

	cmd = ft_cmdtrim(prompt);
	for (int i = 0; i < ft_charpplen(cmd); i++)
		printf("before: %s\n", cmd[i]);
	cmd = ft_expand_vars(cmd);
	for (int i = 0; i < ft_charpplen(cmd); i++)
		printf("after: %s\n", cmd[i]);
    ft_charppfree(cmd);
}
