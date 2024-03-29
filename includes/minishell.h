/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:55:13 by ysingh            #+#    #+#             */
/*   Updated: 2023/08/18 15:11:13 by alvalope         ###   ########.fr       */
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
# include <errno.h>
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
# define FWHITE "\033[0;97m"
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

typedef struct s_pipe_redirect
{
	int			pipe;
	int			re;
}				t_pipe_redirect;

typedef struct s_master
{
	t_strings	strs;
	t_envp		*var;
	t_count		count;
}				t_master;

typedef struct s_global
{
	t_list		*envp;
	char		**env;
	char		**path;
	int			exit_status;
	char		**heredoc_out;
	char		*user;
	char		*dir;
}				t_global;

typedef struct pipex
{
	char		**archive_lines;
	int			lines;
	char		**paths;
	char		***args;
	int			*n_args;
	char		**infile;
	int			*heredoc;
	char		**outfl;
	int			*outmode;
	int			*command_not_found;
	int			i;
}				t_pipex;

typedef struct s_aux
{
	int			i;
	int			pipes;
	int			cmd;
	int			args;
}				t_aux;

t_global		g_global;

int				__quote_state(char c, int old_state);
int				ft_check_cmd(char *prompt);
void			ft_init_global(char **envp);
char			*ft_get_env(char *key);
char			*ft_readline(void);
int				quote_state(char c);
char			**ft_str_add_back(char **str, char *add);
char			**ft_cmdtrim(char *prompt);
char			**ft_parser(char *promt);
char			**ft_expand_vars(char **cmd);
void			ft_add_dollar(void);
char			*ft_add_quote(char *str);
int				__qs(char c, int reset);
char			*ft_dq(char *prompt, int i);
char			*ft_sq(char *prompt, int i);
char			*ft_noq(char *prompt, int i);
char			*ft_strchrs(const char *str, const char *chrs);
int				wordlen_perso(char *prompt, int i);
void			handle_sigint(int sig);
char			*ft_get_var(char *cmd);
char			*ft_red(char *prompt, int i);
char			*ft_redback(char *prompt, int i);
char			*ft_redpipe(char *prompt, int i);
char			*ft_call_dq(char *prompt, int *i);
char			*ft_call_sq(char *prompt, int *i);
char			*ft_call_red(char *prompt, int *i);
char			*ft_call_redback(char *prompt, int *i);
char			*ft_call_pipe(char *prompt, int *i);
char			*ft_call_redpipe(char *prompt, int *i);
int				ft_vr(char *str, int *i);
int				ft_locate_firstpipe(char *str);
void			set_pipe_redirect(int *pipe, int *redirect, int flag);
int				ft_check_last_pipe(char *str);
int				ft_validate(char *str);
void			handle_eof(char *line);
void			ft_init_count(t_pipe_redirect *count, int *i);
void			call_signal(void);
void			ft_error(char *str, char *line);
void			get_dir(void);
void			search_and_replace(t_list *head, const char *key,
					const char *new_value);
char			**remove_quotes_in_array(char **str_array);
void			printg_status(char *error, int status);
int				check_pwd(void);
void			do_cd(char *path, int flag);
void			update_pwd(void);
void			do_exit(int status);
void			if_no_builtin(t_pipex *p, t_aux *auxs, char **argv,
					char **paths);
int				ft_open_in_file(t_pipex *p, int fd[2]);
void			ft_open_out_file(t_pipex *p, int fd2[2]);
int				ft_open_first_file(t_pipex *p, int *file);
void			ft_open_first_out_file(t_pipex *p, int fd[2], int n_com);

void			ft_reserve_mem(t_pipex *p, int cmd, int max_args);
char			*ft_check_comm(char **paths, char *comm, t_pipex *p, int cmd);
int				ft_count_pipes(char *argv[], int n);
int				ft_count_max_args(char *argv[], int n, int i);
void			ft_count_args(char *argv[], int n, t_pipex *p);

void			ft_free_all(t_pipex *p);
void			ft_write_error(char *type, char *error, char *obj);
int				ft_check_outfile(t_pipex *p, t_aux *auxs, char **argv);
int				ft_check_io_fl(t_pipex *p, t_aux *auxs, char **argv, int file);

int				ft_do_last_comm(t_pipex *p, int fd[2], pid_t pid);
int				ft_do_first_comm(t_pipex *p, int fd[2], int n_com);

int				ft_do_commands(t_pipex *p, int argc);

void			ft_heredoc(t_pipex *p, int *file);
void			ft_do_heredoc(t_pipex *p);

void			free_strs(char **result, int index);
char			**ft_split_quote(char const *s, char c);

void			ft_free_mem(t_pipex *p, int cmd);

void			ft_executer(char **cmds, char **paths);
void			ft_main(char **argv, int argc, char **paths, t_aux auxs);
void			execute_builtin(t_pipex *p, int fd[2], int status, int i);
int				get_builtin(char *cmd);
void			execute_echo(char **args);
void			execute_export(char **args);
void			execute_env(int flag);
void			execute_cd(char **args);
void			execute_exit(char **args);
int				search_var(char *key);
void			execute_pwd(void);
void			execute_unset(char **args);
void			assign_var(t_envp *var, char *arg);
void			get_new_var(t_envp var);
void			set_temp_path(void);
void			free_env(void);
void			do_call(t_pipex *p, t_aux auxs, char **argv, int argc);
void			do_cpy(char *temp, char *new_str, t_count *count);
void			if_squote(char *temp, char *new_str, t_count *count);
void			if_dquote(char *temp, char *new_str, t_count *count);
void			free_var(t_envp *var);
int				ft_do_else(t_pipex *p, int fd[2]);
int				ft_do_commands2(t_pipex *p, int n_com);
int				ft_do_command(t_pipex *p, int fd[2], int fd2[2]);
int				ft_do_command2builtin(t_pipex *p, int fd[2], int fd2[]);
int				condition(t_master mas);
int				condition2(char *cmd, t_master mas);
int				condition3(t_master mas);
void			if_dollar_int(t_master *mas);
void			init_all(t_master *mas, char *cmd);
void			do_search_and_replace(char *key, char *value);

#endif
