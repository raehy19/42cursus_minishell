/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:58:02 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/15 09:53:04 by yeepark          ###   ########.fr       */
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
	REDIRECT_INPUT,
	HERE_DOC,
	REDIRECT_OUTPUT,
	APPENDING_REDIRECT_OUTPUT,
}	t_redirect_type;

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

	// node_type == redirect
	t_redirect_type	redirect_type;
	char			*redirect_filename;
	int				in_fd; // initialize STDIN
	int				out_fd; // initialize STDOUT

	// ?
	pid_t			pid;

}	t_node;

typedef struct s_global
{
	int		exit_status;
	char	**envp;
	char	**path;
}	t_global;

#endif
