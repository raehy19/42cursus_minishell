/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:31 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/17 14:02:33 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	process_heredoc(t_node *node)
{
	int		fd[2];
	char	*input;

	node->redirect_filename = ft_combine_lump(node->redirect_linked_str);
	if (pipe(fd))
		g_global.err_num = FAIL_OPEN_PIPE;
	input = 0;
	while (ft_strcmp(input, node->redirect_filename))
	{
		write(fd[WRITE], input, ft_strlen(input));
		if (input)
			write(fd[WRITE], "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	close(fd[WRITE]);
	node->in_fd = fd[READ];
}

void	search_heredoc(t_node *node)
{
	if (node->left)
		search_heredoc(node->left);
	if (node->right)
		search_heredoc(node->right);
	if (node->redirect_type == HERE_DOCUMENT)
		process_heredoc(node);
}
