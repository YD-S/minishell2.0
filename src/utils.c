
#include "minishell.h"

int	quote_state(char c)
{
	static int	old_state;
	int			old_old_state;

	old_old_state = old_state;
	if (!c)
	{
		old_state = NOQUOTE;
		return (0);
	}
	old_state = __quote_state(c, old_old_state);
	return (old_state);
}

int	__quote_state(char c, int old_state)
{
	int	state;

	if (c == '"')
	{
		if (old_state == DQUOTE)
		{
			state = NOQUOTE;
			return (state);
		}
		else if (old_state == NOQUOTE)
			return (DQUOTE);
	}
	else if (c == '\'')
	{
		if (old_state == SQUOTE)
		{
			state = NOQUOTE;
			return (state);
		}
		else if (old_state == NOQUOTE)
			return (SQUOTE);
	}
	return (old_state);
}

void	ft_check_cmd(char *prompt)
{
	int	state;
	int	i;

	quote_state('\0');
	state = NOQUOTE;
	i = 0;
	while (prompt[i])
	{
		state = quote_state(prompt[i]);
		i++;
	}
	if (state != NOQUOTE)
	{
		ft_printf("Quote Error\n");
		exit(0);
	}
}

void	ft_print_lists(void)
{
	t_list	*tmp;
	t_envp	*env;

	tmp = g_global.envp;
	while (tmp)
	{
		env = tmp->content;
		tmp = tmp->next;
	}
	(void)env;
}

char	**ft_str_add_back(char **str, char *add)
{
	int		temp_len;
	int		len;
	char	**ret;

	len = ft_charpplen(str);
	temp_len = len;
	ret = ft_calloc(sizeof(char *), len + 2);
	while (len--)
		ret[len] = str[len];
	ret[temp_len] = add;
	free(str);
	return (ret);
}

char	**ft_cmdtrim(char *prompt)
{
	char	**ret;
	int		j;
	int		k;

	j = 0;
	k = 0;
	ret = NULL;
	while (j < (int)ft_strlen(prompt))
	{
		while (prompt[j] && (prompt[j] == ' '
				&& quote_state(prompt[j]) == NOQUOTE))
			j++;
		k = 0;
		if (SQUOTE == prompt[j + k] || DQUOTE == prompt[j + k])
			while (prompt[j + k] && (prompt[j + k] != ' ' && quote_state(prompt[j
					+ k]) != NOQUOTE))
				k++;
		else
			while (prompt[j + k] && (prompt[j + k] != ' ' && quote_state(prompt[j
					+ k]) == NOQUOTE))
				k++;
		ret = ft_str_add_back(ret, ft_substr(prompt, j, k));
		j += k;
	}
	return (ret);
}

char	*ft_strnstr_perso(const char *haystack, const char *needle, size_t len)
{
	unsigned int i;

	i = 0;
	if (*needle == 0 || haystack == needle)
		return ((char *)haystack);
	i = ft_strlen(needle);
	while (*haystack && i <= len)
	{
		if (!(ft_strncmp((char *)haystack, (char *)needle, i))
			&& !ft_isalnum(*(haystack + i)) && *(haystack + i) != '_')
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}