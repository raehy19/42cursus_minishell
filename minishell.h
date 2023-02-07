/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:58:02 by rjeong            #+#    #+#             */
/*   Updated: 2023/02/07 17:16:55 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_pipe_node		t_pipe_node;
typedef struct s_cmd_node		t_cmd_node;
typedef struct s_redirect_node	t_redirect_node;

typedef struct s_pipe_node {
	t_cmd_node	*cmd_node;
	t_pipe_node	*pipe_node;
} t_pipe_node;

typedef struct s_logical_node {
	t_cmd_node	*cmd_node;
	t_pipe_node	*pipe_node;
} t_logical_node;

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

// logical_type == pipe, and, or, null ==> 명령어 뒤에 오는 | , &&, || , eof 
typedef struct s_big_node {
	int				node_type; // logical cmd redirect
	t_big_node		*cmd_node; // 
	char 			*command;
	char 			**arguments;
	t_big_node		*next_node; // 
	int				logical_type // 
	t_big_node		*redirect_node; // 
	char			*redirect_type;
	char			*redirect_filename;
	pid_t			pid;
	char			**path;

	t_big_node		*parent_node; // 
	int				child_status;
} t_redirect_node;

