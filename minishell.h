/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:58:02 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/11 14:39:01 by yeepark          ###   ########.fr       */
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
# include "srcs/parse/parse.h"

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
	PIPE,
	AND,
	OR
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
	FAIL_MALLOC,
	SYNTAX_ERR,
	INVALID_IDENTIFIER,
	FAIL_FORK,
	FAIL_OPEN_PIPE,
	FAIL_DUPLICATE_FILDES,
	FAIL_CLOSE_FILDES,
	FAIL_EXECUTE
}	t_error_number;

typedef struct s_node	t_node;

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
	char			**command_arg;
	int				arg_cnt;

	// node_type == redirect
	t_redirect_type	redirect_type;
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
int		clear_env(void);

// env rank

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

#endif
