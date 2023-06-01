/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:55:13 by ysingh            #+#    #+#             */
/*   Updated: 2023/06/01 16:52:52 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NO 0

# define DQ '"'
# define DQO 1
# define DQI 2
# define DQC 3

# define SQ '\''
# define SQO 4
# define SQI 5
# define SQC 6

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>

//Colors Start
# define FRED "\033[0;31m"
# define FGREEN "\033[0;32m"
# define FYELLOW "\033[0;33m"
# define FBLUE "\033[0;34m"
# define FPURPLE "\033[0;35m"
# define NONE "\033[0;37m"
//Colors End

typedef struct s_envp
{
	char		*key;
	char		*value;
}				t_envp;

typedef struct s_strings
{
	char		*cpy;
	char		*aux;
	char		*aux2;
}				t_strings;

typedef struct s_count
{
	int			i;
	int			j;
}				t_count;

typedef struct s_master
{
	t_strings	strs;
	t_envp		*var;
	t_count		count;
}				t_master;

typedef struct s_global
{
	t_list		*envp;
	char		*path;
	int			exit_status;
	char		*heredoc_out;
	char		*user;
	int			flag;
}				t_global;

t_global		g_global;

int				__quote_state(char c, int old_state);
int				ft_check_cmd(char *prompt);
void			ft_init_global(char **envp);
char			*ft_get_env(char *key);
char			*ft_readline(void);
int				quote_state(char c);
char			**ft_str_add_back(char **str, char *add);
char			**ft_cmdtrim(char *prompt);
void			ft_parser(char *promt);
char			**ft_expand_vars(char **cmd);
char			*ft_strnstr_perso(const char *haystack, const char *needle,
					size_t len);
void			ft_add_dollar(void);
void			quote_reset(void);
char			*ft_add_quote(char *str);
int				__qs(char c, int reset);
char			*ft_dq(char *prompt, int i);
char			*ft_sq(char *prompt, int i);
char			*ft_noq(char *prompt, int i);
char			*ft_strchrs(const char *str, const char *chrs);
int				wordlen_perso(char *prompt, int i);
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
char			*ft_get_var(char *cmd);
char			*ft_red(char *prompt, int i);
char			*ft_redback(char *prompt, int i);
char			*ft_redpipe(char *prompt, int i);
void			printcustomascii(void);
char			*ft_call_dq(char *prompt, int *i);
char			*ft_call_sq(char *prompt, int *i);
char			*ft_call_red(char *prompt, int *i);
char			*ft_call_redback(char *prompt, int *i);
char			*ft_call_pipe(char *prompt, int *i);
char			*ft_call_redpipe(char *prompt, int *i);
#endif // MINISHELL_H
