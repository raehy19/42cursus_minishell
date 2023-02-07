/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:58:02 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/07 15:58:43 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_pipe_node		t_pipe_node;
typedef struct s_cmd_node		t_cmd_node;
typedef struct s_redirect_node	t_redirect_node;

typedef struct s_pipe_node {
	t_cmd_node	*cmd_node;
	t_pipe_node	*pipe_node;
} t_pipe_node;

typedef struct s_cmd_node {
	t_redirect_node	*redirect;
	char 			*cmd;
	char 			**arguments;
} t_cmd_node;


typedef struct s_redirect_node {
	t_redirect_node	*redirect;
	char			*redirect_type;
	char			*filename;
} t_redirect_node;

