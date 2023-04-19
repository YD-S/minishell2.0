
#ifndef MINISHELL_H
# define MINISHELL_H
# define DQUOTE 2
# define SQUOTE 1
# define NOQUOTE 0

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
	t_list 	*envp;
	char	*path;
	int		exit_status;
	char	*heredoc_out;
	char	*user;
}			t_global;

t_global g_global;

int			quote_state(char c);
void		ft_check_cmd(char *prompt);
void		ft_init_global(char **envp);
void ft_print_lists(void);
char *ft_get_env(char *key);
char *ft_readline(void);
#endif // MINISHELL_H
