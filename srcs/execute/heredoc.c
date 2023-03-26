/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:31 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/26 16:39:50 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	process_heredoc(t_node *node, int pipe[])
{
	int		newline;
	char	*input;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	newline = 0;
	input = ft_strdup("");
	close_fildes(pipe[READ]);
	node->redirect_filename = ft_combine_lump(&node->redirect_linked_str);
	while (input && ft_strcmp(input, node->redirect_filename))
	{
		write(pipe[WRITE], input, ft_strlen(input));
		if (newline)
			write(pipe[WRITE], "\n", 1);
		free(input);
		input = readline("> ");
		newline = 1;
	}
	free(input);
	close_fildes(pipe[WRITE]);
	exit(0);
}

void	handle_heredoc(t_node *node)
{
	pid_t	pid;
	int		pipe[2];

	open_pipe(pipe);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		g_global.err_num = FAIL_FORK;
		handle_error();
		return ;
	}
	if (pid == 0)
		process_heredoc(node, pipe);
	wait(0);
	close_fildes(pipe[WRITE]);
	node->in_fd = pipe[READ];
}

void	search_heredoc(t_node *node)
{
	if (node->left)
		search_heredoc(node->left);
	if (node->pre_redirect)
		search_heredoc(node->pre_redirect);
	if (node->right)
		search_heredoc(node->right);
	if (node->redirect_type == HERE_DOCUMENT)
		handle_heredoc(node);
}
