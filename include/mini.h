/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:30:37 by sooyoon           #+#    #+#             */
/*   Updated: 2021/01/16 22:48:39 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>

# define MINISHELL 42
# define NAME "minishell"

/*
** boolean
*/

# define FALSE 0
# define TRUE 1

/*
** need to add error
*/

# define ERROR 0
# define NOT_FOUND -1
# define SUCCESS 1
# define NOT_BUILTIN 2

# define PIPE 1
# define INPUT 2
# define OUTPUT 3
# define APPEND 4
# define SEMI 5
# define SPACE 6
# define END 7

# define FORK_ERR 1
# define PATH_ERR 2
# define PARSING_ERR 3
# define COMMAND_ERR 4

struct	s_info
{
	t_list			*env_list;
	char			*process_name;
	int				process_index;
	int				exit_status;
	int				pid;
	int				ppid;
	int				is_minishell;
	int				std[2];
};
typedef struct s_info	t_info;

/*
** cmd_lst : command list
** pro_lst : process list
*/

struct	s_exec
{
	int				*fd[2];
	char			**argv;
	int				fd_count;
	int				fd_input_idx;
	int				fd_output_idx;
	int				std[2];
	int				argv_idx;
	int				input_count;
	int				output_count;
};
typedef struct s_exec	t_exec;

struct	s_pro
{
	int				type;
	char			*raw;
	t_list			*pipe_lst;
	struct s_pro	*next;
};
typedef struct s_pro	t_pro;

struct	s_parse
{
	int				is_space;
	int				is_redirection;
	int				single_q;
	int				double_q;
	int				fd_count;
	int				type;
	size_t			start;
	char			*line;
	t_pro			*pro_lst;
};
typedef struct s_parse	t_parse;

/*
** utils
*/

t_info	*get_info();
size_t	len(char **arr);
int		find_chr(char *str, char ch);
char	*free_join(char *s1, char *s2);
void	ft_sleep(int amount);

/*
** print_utils
*/

void	print_str(void *str);
void	print_err(void *str);
void	print_arr(char **arr);
void	println_arr(char **arr);
void	print_lst(t_list *lst);

/*
** built-ins
*/

int		pwd();
int		cd(char *argv);
int		echo(char **argv);
int		builtin_exit(char **argv);
void	free_exit();

/*
** is_valid
*/

int		valid_path(char *path);
int		valid_first_command(char c);
int		valid_pipe(t_list *pipe_lst);
int		is_valid_line(char **line);

/*
**  env
*/

int		env();
void	sort_env_arr(char **arr);
void	export_only();
int		export(char *argv);
int		unset(char *argv);

/*
** search_env
*/

char	*get_env_item(char *key);
t_list	*create_env_list(char **environ);
char	**get_environ();

/*
** parsing_utils
*/

int		is_semi_char(char c);
int		is_pipe_char(char c);
int		is_redirection_char(char c);
void	init_pars(t_parse *pars);
int		search_quotes(char c, char *line, int i);

/*
** parsing_utils2
*/

int		how2divide(char c);
int		is_error(char c);
int		is_outofquote_end(char c);
int		is_escape(char c);
int		is_sayeon(char c);

/*
** parsing_utils3
*/

void	process_sayeon(char c, char **result);
char	*find_var_name(char *content, size_t *i);
char	*process_home(char *content);
void	is_quotes_true(char c, t_parse *pars);
void	is_quotes_false(char *line, size_t i, t_parse *pars);

/*
** prolist_utils
*/

t_pro	*new_prolst(char *raw, int type);
t_pro	*last_prolst(t_pro *lst);
void	add_back_prolst(t_pro **lst, t_pro *new);
void	free_prolst(t_pro **lst);
void	concat_prolst(t_parse *pars, char *line, size_t i, int type);

/*
** set_items
*/

int		set_string(char **old_str, char *new_str);
int		set_process_name(char *name);

/*
** get_cmd
*/

char	*join_cmd_envpath(char	**path, char *command);
char	*get_cmd(char *cmd);

/*
** free
*/

void	free_parse(t_parse *parse, char *command);
void	free_arr(char **arr);
void	free_exec_info(t_exec **exec_info);
char	*free_strtrim(char **s, char const *set);

/*
** lst_utils
*/

t_list	*new_lst_trim(char *content);
void	add_redirection_lst(t_parse *pars, t_list **lst, int type);

/*
** exec_utils
*/

int		init_exec(t_exec	*exec_info, int lst_count);
t_exec	*create_exec(t_parse *pars, t_list *redir_lst);

/*
** fd
*/

void	get_fd_count(t_list	*redir_lst, t_exec *exec_info);
int		create_fds(t_exec *exec_info, char *redir_str, char *file_str);
void	close_fds(t_exec *exec_info);

/*
** excute_cmd
*/

int		excute_cmd(t_parse *pars, t_list *pipe_lst);
int		execute_builtin(char **argv);

/*
** redirect
*/

int		input_redirection_lst(t_parse *pars, char *raw, t_list **raw_lst);
t_exec	*redir_process(t_parse *pars, t_list *pipe_lst);

/*
** redir_utils
*/

int		is_redir_pipe(char ch);
int		find_multi_redir(char *text);
int		check_continuous(char *str);

/*
** pipe
*/

int		piping(t_parse *pars, t_list *pipe_lst);

/*
** main_utils
*/

void	print_prompt();
void	interrupt_handler(int sig);
int		check_eof(int gnl_value, char **command);

/*
** error
*/

int		print_error(int type, char *path);
int		input_pipe_lst(t_parse *pars, char *raw, t_list **raw_lst);

/*
** parse_pipe
*/

int		make_pipe_lst(t_pro *pro_lst, t_parse *pars);
void	substr_addlst_back(t_list **raw_lst, char *raw, int start, int i);

/*
** parsing
*/

int		main_parse(char *line, t_parse *pars);

/*
** quotes_zone
*/

char	*get_single_quote_zone(char *content, size_t *start, size_t *i);
char	*get_double_quote_zone(char *content, size_t *start, size_t *i);
char	*out_of_quotes_zone(char *content, size_t *start, size_t *i);

/*
** quotes_zone_util
*/

void	fill_result(char **result, char *content,
		size_t *start, size_t *i);
void	fill_result_plus_start(char **result, char *content,
		size_t *start, size_t *i);
void	fill_result_plus_i(char **result, char *content,
		size_t *start, size_t *i);

/*
** process_quotes
*/

char	*process_quotes(t_parse *pars, char *content);

/*
** main
*/

int		get_next_line(int fd, char **line);

#endif
