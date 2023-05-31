/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:09:06 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 23:29:35 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_validate_redirect(char *str, int *i)
{
	int	count;

	count = 0;
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		count += 2;
		*i += 1;
	}
	// else if (str[*i] == '>' && str[*i + 1] != '>')
	// {
	// 	count += 1;
	// 	*i += 1;
	// }
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		count += 2;
		*i += 1;
	}
	// else if (str[*i] == '<' && str[*i + 1] != '<')
	// {
	// 	write(1, "4\n", 2);
	// 	count += 1;
	// 	*i += 1;
	// }
	// else if ((str[*i] != '<' || str[*i] != '>') && str[*i + 1] == ' ')
	// 	{
	// 		write(1, "5\n", 2);
	// 		*i += 1;
	// 	}
	return (count);
}

int	ft_validate(char *str)
{
	int	i;
	int	pflag;
	int	rflag;
	int	count;

	rflag = 0;
	pflag = 1;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] == ' ')
			i++;
		if (str[i] == '|' && rflag)
			return (0);
		if ((str[i] == '>' || str[i] == '<') && pflag)
			return (0);
		if (str[i] == '|' && pflag)
			return (0);
		if (str[i] == '|' && !pflag && !count)
			pflag = 1;
		if (str[i] == '>' || str[i] == '<')
		{
			count = ft_validate_redirect(str, &i);
			printf("%d\n", count);
			if (count > 2)
				return (0);
			rflag = 1;
			pflag = 0;
		}
		if (str[i] != '|' && str[i] != '>' && str[i] != '<')
			pflag = 0;
		i++;
	}
	return (1);
}

int	ft_check_cmd(char *prompt)
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
		return (0);
	}
	__qs('\0', 1);
	return (ft_validate(prompt));
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
		ret[len] = ft_strdup(str[len]);
	ret[temp_len] = ft_strdup(add);
	ft_charppfree(str);
	free(add);
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

void	ft_check_pipe(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	if (count > 1)
	{
		ft_printf("syntax error near unexpected token `|'\n");
		exit(0);
	}
}
