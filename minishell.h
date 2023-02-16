/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:58:02 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/16 20:51:27 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <signal.h>
# include "libft/libft.h"

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
	INVALID_IDENTIFIER
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
	int				exit_status;
	t_env			*envp;
	char			**path;
	t_error_number	errno;
}	t_global;

typedef enum e_parse_type
{
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_REDIRECTING_INPUT,
	T_HERE_DOCUMENT,
	T_REDIRECTING_OUTPUT,
	T_APPENDING_REDIRECTED_OUTPUT,
	T_SEMICOLON,
	T_LEFT_PARENTHESIS,
	T_RIGHT_PARENTHESIS,
	T_AND,
	T_OR,
	T_PIPE,
	T_STRING,
}	t_parse_type;

typedef struct s_parse_node
{
}	t_parse_node;


// envp

int		init_envp(char *envp[]);

int		ft_index(char *str, int c);
int		is_valid_name(char *str);
t_env	*make_env(char *src);
void	add_env_back(t_env *new);
void	remove_env(char *name);
int		clear_env(void);

// export

void	ft_export(t_node *node);

void	init_rank(void);
int		get_envp_size(void);
t_env	*get_largest_env(void);
void	rank_envp(void);

#endif
