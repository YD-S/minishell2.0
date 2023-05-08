
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
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>

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
	char	*key;
	char	*value;
}			t_envp;

typedef struct s_global
{
	t_list	*envp;
	char	*path;
	int		exit_status;
	char	*heredoc_out;
	char	*user;
}			t_global;

t_global	g_global;

int			__quote_state(char c, int old_state);
void		ft_check_cmd(char *prompt);
void		ft_init_global(char **envp);
// DEBUG
void		ft_print_lists(void);
// END DEBUG
char		*ft_get_env(char *key);
char		*ft_readline(void);
int			quote_state(char c);
char		**ft_str_add_back(char **str, char *add);
char		**ft_cmdtrim(char *prompt);
void		ft_parser(char *promt);
char		**ft_expand_vars(char **cmd);
char		*ft_strnstr_perso(const char *haystack, const char *needle,
				size_t len);
void		ft_add_dollar(void);
void		quote_reset(void);
char		*ft_add_quote(char *str);
int			__qs(char c, int reset);

#endif // MINISHELL_H
