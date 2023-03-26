/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:06:03 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/26 20:51:41 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1

# define OLD 0
# define NEW 1

# define STDIN 0
# define STDOUT 1

char	**make_two_dim(char	**array, int size);
typedef enum e_node_type
{
	LOGICAL,
	COMMAND,
	REDIRECT
}	t_node_type;

typedef enum e_logical_type
{
	NaL,
	ROOT,
	AND,
	OR,
	PIPE
}	t_logical_type;

typedef enum e_builtin_type
{
	NaB,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin_type;

typedef enum e_redirect_type
{
	NaR,
	REDIRECTING_INPUT,
	HERE_DOCUMENT,
	REDIRECTING_OUTPUT,
	APPENDING_REDIRECTED_OUTPUT,
}	t_redirect_type;

typedef enum e_error_number
{
	NaE,
	SYNTAX_ERR,
	INVALID_IDENTIFIER,
	NO_SUCH_FILE,
	COMMAND_NOT_FOUND,
	IS_DIRECTORY,
	FAIL_MALLOC,
	FAIL_FORK,
	FAIL_OPEN_FILDES,
	FAIL_CLOSE_FILDES,
	FAIL_OPEN_PIPE,
	FAIL_DUPLICATE_FILDES,
	FAIL_EXECUTE,
	FAIL_OPEN_DIR
}	t_error_number;

typedef struct s_node		t_node;

// tokenize

typedef enum e_token_type
{
	T_LEFT_PARENTHESIS,
	T_RIGHT_PARENTHESIS,
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIRECTING_INPUT,
	T_HERE_DOCUMENT,
	T_REDIRECTING_OUTPUT,
	T_APPENDING_REDIRECTED_OUTPUT,
	T_WHITESPACE,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_STRING,
	T_LUMP_STR,
}	t_token_type;

typedef struct s_link_str	t_link_str;

typedef struct s_link_str
{
	char			*str;
	t_token_type	str_type;
	t_link_str		*next;
}	t_link_str;

typedef struct s_linked_arg	t_linked_arg;

typedef struct s_linked_arg
{
	t_link_str		*arg_str;
	t_linked_arg	*next;
}	t_linked_arg;

typedef struct s_token_node	t_token;

typedef struct s_token_node
{
	t_token_type	type;
	char			*str;
	t_token			*next;
	t_link_str		*link_str;
}	t_token;

// parsed

typedef struct s_parsed
{
	t_token	*token_list;
	t_token	*compressed_list;
	t_node	*tree;
}	t_parsed;

// tokenize utils

t_token			*new_token(t_token_type type, char *str);
t_token			*lst_last_token(t_token *lst);
void			lst_push_token(t_token **lst, t_token *new);
t_token			*token_shift(t_token **token_list);
void			token_unshift(t_token **lst, t_token *new);

// tokenize

void			tokenize_whitespace(char *str, int *idx, t_token **lst);
void			tokenize_parenthesis(char *str, int *idx, t_token **lst);
void			tokenize_and_or_pipe(char *str, int *idx, t_token **lst);
void			tokenize_arrows(char *str, int *idx, t_token **lst);
void			tokenize_single_quote(char *str, int *idx, t_token **lst);
void			tokenize_double_quote(char *str, int *idx, t_token **lst);
void			tokenize_string(char *str, int *idx, t_token **lst);

int				is_string_char(char c);
t_token			*ft_tokenize(char *input);

// token compress utils

int				is_string(t_token *token);
t_link_str		*new_link_str(t_token_type type, char *str);
t_link_str		*link_str_last(t_link_str *lst);
void			link_str_add_back(t_link_str **lst, t_link_str *new);

// token compress

void			ft_combine_str(t_token *temp,
					t_link_str **linked_str, t_token **token_list);
void			compress_str_node(t_token *temp,
					t_token **compressed_token_list, t_token **token_list);
t_token			*compress_tokens(t_token **token_list);

// parse

t_node			*make_tree(t_token **token_list);
void			parse(char *input, t_parsed *parsed);

// check token

int				check_token_list(t_token **token_list);

// parse_utils

t_node			*new_node(t_node_type type, t_logical_type logical_type);
void			node_unshift(t_node **lst, t_node *new);
void			lst_push_cmd(t_linked_arg **lst, t_link_str *arg);
int				is_string_char(char c);
int				is_and_or_pipe(t_token *temp);
int				is_parenthesis(t_token *temp);
int				is_logical(t_token *temp);
int				is_arrow(t_token *temp);

// parse_token

t_token			*parse_l_parenthesis(t_node **head,
					t_token *temp, t_token **token_list);
t_token			*parse_r_parenthesis(t_node **head,
					t_token *temp, t_token **token_list);
void			parse_parenthesis(t_node **head,
					t_token **temp, t_token **token_list);
void			parse_arrow(t_node **arrow,
					t_token *temp, t_token **token_list);
void			parse_cmd(t_linked_arg **cmd_args, t_token *temp);
void			add_new_logical(t_node **head,
					t_token *temp, t_token **token_list);
void			ft_check_cmd(t_node **head,
					t_linked_arg *cmd_args, t_node *arrow);
void			parse_token_list(t_node **head, t_token **token_list);

t_token			*token_shift(t_token **token_list);
void			node_unshift(t_node **lst, t_node *new);
void			parse_token_list(t_node **head, t_token **token_list);

// parse on excute

char			*ft_combine_lump(t_link_str **head);
char			**ft_combine_arg(t_linked_arg **head, int *arg_cnt);

// check_env

void			check_env(char **str);

void			lst_push_cmd(t_linked_arg **lst, t_link_str *arg);

// signal

void			signal_handler(int signo);
void			handle_signal(void);

// terminal

void			set_control_character(void);
void			unset_comtrol_character(void);

typedef struct s_execute
{
	int		cnt;
	int		in_subshell;
	int		pre_redirect;
	int		pipe[2][2];
	pid_t	pid;
}	t_execute;

typedef struct s_node
{
	t_node_type		type;
	t_node			*pre_redirect;
	t_node			*left;
	t_node			*right;

	// node_type == logical
	t_logical_type	logical_type;

	// node_type == command
	char			*command_path;
	t_linked_arg	*cmd_arg_linked_str;
	char			**command_arg;
	int				arg_cnt;
	t_builtin_type	builtin_type;

	// node_type == redirect
	t_redirect_type	redirect_type;
	t_link_str		*redirect_linked_str;
	char			*redirect_filename;
	int				in_fd; // initialize STDIN
	int				out_fd; // initialize STDOUT
	// ?
	pid_t			pid;

}	t_node;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				order;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	unsigned char	exit_status;
	t_env			*envp;
	t_error_number	err_num;
	void			(*builtin_function[8])(t_node *);
	int				standard_fildes[2];
	int				is_child;
}	t_global;

//global

void			init_global(char **envp);
int				init_envp(char *envp[]);
void			init_builtin_functions(void);

// env

int				is_valid_name(char *str);
char			*make_name(char *src, int index);
void			set_node(t_node **node, char *src);
t_env			*make_env(char *src);
void			add_env_back(t_env *new);

int				get_env_size(void);
t_env			*find_env(char *name);
char			**make_envp(void);

void			remove_env(char *name);
void			clear_one_env(t_env **env);
int				clear_env(void);

void			init_env_order(void);
t_env			*get_largest_env(void);
void			rank_envp(void);

// tree

void			search_tree(t_node *node);
void			search_node(t_node *node);
void			handle_node(t_node *node);
void			handle_process(t_node *node, t_execute *execute);
void			handle_child_process(t_node *node, t_execute *execute);
void			handle_parent_process(t_node *node, t_execute *execute);
void			wait_process(t_execute *execute);

// builtin

int				handle_singlebuiltin(t_node *node);
void			set_builtin_type(t_node *node);

void			ft_echo(t_node *node);
void			ft_cd(t_node *node);
void			ft_pwd(t_node *node);
void			ft_export(t_node *node);
void			ft_unset(t_node *node);
void			ft_env(t_node *node);
void			ft_exit(t_node *node);

// redirect

void			handle_redirect(t_node *node);
void			search_heredoc(t_node *node);
void			process_heredoc(t_node *node, int pipe[]);
void			handle_heredoc(t_node *node);

void			open_pipe(int fd[2]);
void			close_pipe(int pipe[2]);
int				open_fildes(char *file_name, int oflag, int mode);
void			close_fildes(int fd);
void			init_standard_fildes(void);
void			duplicate_standard_fildes(int fd);
void			duplicate_fildes(int fd1, int fd2);

// command

void			handle_builtin(t_node *node);
void			execve_command(t_node *node);
void			handle_command(t_node *node);
char			*find_command_path(t_node *node);

// file

int				is_directory(mode_t st_mode);
int				is_regular_file(mode_t st_mode);

// error

void			print_command_error(t_node *node, int idx, char *error_message);
void			print_command_path_error(t_node *node, int idx);
void			print_invalid_identifier_error(t_node *node, int idx);
void			print_redirect_error(char *filename, char *error_message);
void			handle_error(void);

// utils

int				free_two_dim(char **array);
void			free_command_node(t_node *node);
void			free_redirect_node(t_node *node);
void			free_node(t_node *node);
void			free_tree(t_node *node);
void			free_link_str(t_link_str **link_str_list);
void			free_token_list(t_token **token_list);
void			free_cmd_arg_linked(t_linked_arg *linked_arg_list);

// bonus

int				check_fork(t_node *node);
int				check_exit_status(t_node *node);
int				handle_and_or(t_node *node, t_execute *execute);
int				handle_parenthesis(t_node **node, t_execute *execute);

// wildcard

void			handle_redirect_wildcard(t_node *node);
void			handle_command_wildcard(t_node *node);
int				is_wildcard_format(char *name, char *format);
int				is_wildcard(char c);
void			add_new_list(t_list **command_lst, char *name);
char			**make_command_arg(t_list *command_lst);
void			handle_wildcard_error(t_node *node,
					char *new_filename, int cnt);
#endif
