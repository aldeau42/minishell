/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:06:41 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:06:44 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "mem/mem.h"
# include "libft/libft.h"
# include <signal.h>

# define _XOPEN_SOURCE 700
# define PATH_MAX   4096

extern int	g_signal_flag;

// LC ARGUMENT TOKEN
typedef struct s_token
{
	char			*prompt;
	int				type;
	struct s_token	*next;
}		t_token;

typedef struct s_lst
{
	t_token		*head;
}	t_lst;

typedef struct s_gbl
{
	t_gcan	gc;
	char	**mini_env;
	char	**exp_env;
	char	*input;
	char	*new_line;
	int		printexp;
	char	*i_v;
	char	*path_temp;
	int		st;
	int		lg_str;
	char	**history_tab;
	int		history_count;
	char	*cur_pwd;
	char	*new_pwd;
	int		exit_ret;
	int		cmd_not_found;
	int		cmd_num;
	int		cmd_ind;
	int		pipe_num;
	int		pipe_end;
	int		prev_fd;
	int		out_fd;
	int		pid;
	int		flag;
	int		sigaction_flag;
	int		status;
	int		path;
	int		next_pipe;
	int		pipe_limiter;
	int		limiter_fd;
	int		cat;
	int		used_limiter;
	int		bot;
	t_lst	*t_lst;
}	t_gbl;

// MAIN
void	main_loop(t_gbl *gbl, t_lst *t_lst);
int		main(int argc, char **argv, char **env);

// FONCTION PARSING
int		parsing(t_gbl *gbl, t_lst *t_lst);
int		quote_check(char *input);
void	quote_var_env(t_gbl *gbl, int *i, int *j);
void	quote_var_env2(t_gbl *gbl, int *i, int *j);
int		var_env_chang(t_gbl *gbl, t_lst *lst);
int		check_pipe_at_start(t_gbl *gbl);
int		add_var(t_gbl *gbl, int i, int o, t_lst *lst);
int		add_list_exec(t_gbl *gbl, t_lst *token_list);
void	add_list_exec_error(t_gbl *gbl, t_lst *lst, int c);
void	put_maillon_str(t_gbl *gbl, t_lst *token_list);
int		put_entry(t_gbl *sg, t_lst *t_lst);
int		put_sorti(t_gbl *gbl, t_lst *t_lst);
void	pass_quote(t_gbl *sg, int *i, char quote);
int		check_var(t_gbl *gbl, int i);
void	trim_spaces(char *str);
int		count_args(char **args);
int		check_arg(char *arg);
int		ft_isnum(char *str);
int		is_same_var(char *envline, char *input);
char	*ft_clear_env(char *str, t_gbl *gbl);
int		get_env(t_gbl *gbl, int opt);
int		check_pipe_at_end(t_gbl *gbl);
void	clone_env(t_gbl *gbl, char **env);
void	modif_exp(t_gbl *gbl, int i);
char	*change_inp(t_gbl *gbl);
int		check_dir(t_gbl *gbl);
char	*chaeck_var2(t_gbl *gbl, int opt);
int		add_var_interro(t_gbl *gbl, int i);

// EXECUTING LINKED LISTS
void	add_token(t_lst *t_lst, char *prompt, int type, t_gbl *gbl);

// EXEC
void	start_exec(t_gbl *gbl, t_lst *t_lst);
void	pipe_handler(t_gbl *gbl, int *pipe_fd);
void	pipe_handler2(t_gbl *gbl);
int		single_entry(char *infile, t_gbl *gbl);
int		single_exit(char *outfile, t_gbl *gbl);
int		double_exit(char *outfile, t_gbl *gbl);
void	ft_heredoc_input(char *input, int *pipe_fd);
int		limiter_fd(char *limiter, t_gbl *gbl);
int		core_exec(t_gbl *gbl, char *prompt, t_lst *lst);
void	child_process_exec(t_gbl *gbl, char *prompt, char *input, t_lst *lst);
void	execute(t_gbl *gbl, char *prompt);
void	execute_2(t_gbl *gbl, char *prompt);
char	*pathfinder(t_gbl *gbl, char **arg, char *prompt);
char	*absolute_path(char *path);
void	pathfinder_errors(t_gbl *gbl, char *prompt);
void	pipe_at_end(t_gbl *gbl, t_lst *lst);
void	redirections_fd(t_gbl *gbl, t_token *lst_ptr);
void	cmd_pipe_counter(t_gbl *gbl, t_lst *lst);
char	*absolute_path(char *path);
t_token	*next_prompt(t_gbl *gbl, t_token *lst_ptr);
t_token	*cat_exception(t_gbl *gbl, t_token *lst_ptr);
t_token	*cat_exception2(t_gbl *gbl, t_token *lst_ptr);
t_token	*remove_chev(t_token *lst_ptr, t_gbl *gbl);

// BUILTINS
int		if_builtin_redir(t_gbl *gbl, char *input);
int		if_builtin_no_redir(t_gbl *gbl, char *input, t_lst *lst);
void	own_env(t_gbl *gbl);
int		own_pwd(t_gbl *gbl);
int		own_export(char *input, t_gbl *gbl);
void	swap_export(t_gbl *gbl);
void	own_echo(char *input, t_gbl *gbl);
void	own_exit(char *input, t_gbl *gbl, t_lst *lst);
void	own_cd(char *str, t_gbl *gbl);
void	own_unset(char *input, t_gbl *gbl);
void	print_export(t_gbl *gbl);
void	add_env(char *arg, t_gbl *gbl);

// SIGNAL MANAGEMENT
void	treat_signal(void);
void	signal_handler(int signal);
void	signal_handler2(int sig);
void	handle_exit_status(t_gbl *gbl);

// EXIT
void	error_msg(char *msg, t_gbl *gbl);
void	clear_t_lst(t_lst *t_lst);
void	quit_exit_pars(t_gbl *gbl, t_lst *lst);
void	quit_exit(t_gbl *gbl, char **args, t_lst *lst);
void	quit_exit_exec(t_gbl *gbl, char *input, t_lst *lst);

// FONCTION UTILS
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
char	*ft_gcstrdup(const char *s, t_gbl *gbl);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcat(char *dest, char *src);
int		count_args(char **args);
int		check_arg(char *arg);
int		ft_isnum(char *str);
int		skip_space(char *string, int i);
void	free_split(char **str);
int		is_equal(char *s);

//UTILS MAX
void	error_mnger(char *str, int n);
void	ft_free_tab(char **str);
size_t	ft_strlen_max(const char *s);
char	*ft_strnstr_max(const char *big, const char *little, size_t len);
char	*ft_strjoin_max(char const *s1, char const *s2);
char	*ft_strcpy2(char *s1, const char *s2, int start, int end);
char	**get_tab(char **tab, char *str, char c, int *len);
int		get_wc(char *str, char c);
int		*get_wl(char *str, char c, int wc);
char	**ft_split_max(char *str, char c);
char	*ft_strdup_max(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp_max(const char *s1, const char *s2, size_t n);
char	*ft_remove_option(char *prompt, char *input);
int		check_path(t_gbl *gbl);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

#endif
