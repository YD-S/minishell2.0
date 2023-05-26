
#include "minishell.h"

void	ft_check_cmd(char *prompt)
{
	int	state;
	int	i;

	__qs('\0', 1);
	state = NO;
	i = 0;
	while (prompt[i])
	{
		state = quote_state(prompt[i]);
		i++;
	}
	if (state != NO && state != SQC && state != DQC)
	{
		ft_printf("Quote Error\n");
		exit(0);
	}
	__qs('\0', 1);
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
	ft_charppfree(str);
	return (ret);
}

char	**ft_cmdtrim(char *prompt)
{
	char	**ret;
	char	*aux;
	int		i;

	//int qs;
	i = 0;
	ret = NULL;
	while (i < (int)ft_strlen(prompt))
	{
		/*	qs = quote_state(prompt[i]);
		if (qs == NO && prompt[i] == ' ')
			j++;
		else if (qs == NO || qs == SQI || qs == DQI)
			k++;
		else if (((qs == SQO || qs == DQO) && k != 0) || qs == SQC || qs == DQC
				|| i == (int)ft_strlen(prompt) - 1)
		{
			ret = ft_str_add_back(ret, ft_substr(prompt, j, k + (qs == SQC
							|| qs == DQC) * 2));
			j += k + (qs == SQC || qs == DQC || qs == NO) * 2;
			k = 0;
		}
		i++;
		*/
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == DQ)
		{
			aux = ft_dq(prompt, i);
			i += ft_strlen(aux);
		}
		else if (prompt[i] == SQ)
		{
			aux = ft_sq(prompt, i);
			i += ft_strlen(aux);
		}
		else
		{
			aux = ft_noq(prompt, i);
			i += ft_strlen(aux);
		}
		ret = ft_str_add_back(ret, aux);
	}
	return (ret);
}

char	*ft_strchrs(const char *str, const char *chrs)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (chrs[j])
		{
			if (str[i] == chrs[j])
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr_perso(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;

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
