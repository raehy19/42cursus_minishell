/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:58:02 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/11 17:27:43 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1

# define OLD 0
# define NEW 1

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
	FAIL_MALLOC,
	FAIL_FORK,
	FAIL_OPEN_PIPE,
	FAIL_DUPLICATE_FILDES,
	FAIL_CLOSE_FILDES,
	FAIL_EXECUTE
}	t_error_number;

typedef struct s_node	t_node;

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

typedef struct s_linked_str	t_linked_str;

typedef struct s_linked_str
{
	char			*str;
	t_token_type	str_type;
	t_linked_str	*next;
}	t_linked_str;

typedef struct s_token_node	t_token_node;

typedef struct s_token_node
{
	t_token_type	type;
	char			*str;
	t_token_node	*next;
	t_linked_str	*linked_str;
}	t_token_node;

t_token_node	*new_token(t_token_type type, char *str);
t_token_node	*lst_last_token(t_token_node *lst);
void			lst_push_token(t_token_node **lst, t_token_node *new);
int				is_string_char(char c);

void			tokenize_whitespace(char *str, int *idx, t_token_node **lst);
void			tokenize_parenthesis(char *str, int *idx, t_token_node **lst);
void			tokenize_and_or_pipe(char *str, int *idx, t_token_node **lst);
void			tokenize_arrows(char *str, int *idx, t_token_node **lst);
void			tokenize_single_quote(char *str, int *idx, t_token_node **lst);
void			tokenize_double_quote(char *str, int *idx, t_token_node **lst);
void			tokenize_string(char *str, int *idx, t_token_node **lst);

t_token_node	*ft_tokenize(char *input);

// compress

int	is_string(t_token_node *token);
t_linked_str	*new_linked_str(t_token_type type, char *str);
t_linked_str	*lst_last_linked_str(t_linked_str *lst);
void	lst_add_back_linked_str(t_linked_str **lst, t_linked_str *new);

t_token_node	*compress_tokens(t_token_node **token_list);


// parse

t_node	*new_node(t_node_type type, t_logical_type logical_type);
void	lst_unshift_token(t_node **lst, t_node *new);
t_node	*ft_parse(t_token_node **token_list);
void	ft_parse_token_list(t_node **head, t_token_node **token_list);

typedef struct s_linked_arg t_linked_arg;

typedef struct s_linked_arg
{
	t_linked_str	*arg_str;
	t_linked_arg	*next;
}	t_linked_arg;

void	lst_push_cmd(t_linked_arg **lst, t_linked_str *arg);

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

	// node_type == redirect
	t_redirect_type	redirect_type;
	t_linked_str	*redirect_linked_str;
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
	int				is_singlebuiltin;
}	t_global;

// env

int		init_envp(char *envp[]);

int		is_valid_name(char *str);
char	*make_name(char *src, int index);
void	set_node(t_node **node, char *src);
t_env	*make_env(char *src);
void	add_env_back(t_env *new);

int		get_env_size(void);
t_env	*find_env(char *name);
char	**make_envp(void);

void	remove_env(char *name);
void	clear_one_env(t_env **env);
int		clear_env(void);


void	init_env_order(void);
t_env	*get_largest_env(void);
void	rank_envp(void);

// tree

void	search_tree(t_node *node);
void	search_node(t_node *node);
void	handle_node(t_node *node);
void	handle_child_process(t_node *node, int pipe[2][2], int cnt);
void	handle_parent_process(t_node *node, int pipe[2][2]);

// builtin

int		handle_singlebuiltin(t_node *node);
void	set_singlebuiltin(t_node *node);

void	ft_echo(t_node *node);
void	ft_cd(t_node *node);
void	ft_pwd(void);
void	ft_export(t_node *node);
void	ft_unset(t_node *node);
void	ft_env(void);
void	ft_exit(t_node *node);

// redirect

void	handle_redirect(t_node *node);
void	search_heredoc(t_node *node);
void	process_heredoc(t_node *node);

void	open_pipe(int fd[2]);
void	close_pipe(int pipe[2]);
void	close_fildes(int fd);
void	duplicate_fildes(int fd1, int fd2);

// command

void	handle_builtin(t_node *node);
void	execve_command(t_node *node);
void	handle_command(t_node *node);
char	*find_command_path(t_node *node);

// error

void	print_command_error(t_node *node, int idx, char *error_message);
void	print_invalid_identifier_error(t_node *node, int idx);
void	print_redirect_error(char *filename);
void	handle_error(void);
void	exit_by_global(void);

#endif
