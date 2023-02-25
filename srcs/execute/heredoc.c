/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:31 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 20:48:28 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//extern t_global	g_global;
t_global	g_global;

void	process_heredoc(t_node *node)
{
	int		fd[2];
	char	*input;
	
	if (pipe(fd))
		g_global.errno = FAIL_OPEN_PIPE;
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
//	char buf[4096];
//	read(fd[READ], buf, 4096);
//	printf("delimeter : %s buf :%s\n", node->redirect_filename, buf);
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

//#include <string.h>
//
//int	main(void)
//{
//	t_node	*node = malloc(sizeof(t_node));
//
//	node->redirect_filename = strdup("eof");
//	node->redirect_type = HERE_DOCUMENT;
//	node->left = 0;
//	node->right = malloc(sizeof(t_node));
//	
//	node->right->redirect_filename = strdup("asdf");
//	node->right->redirect_type = HERE_DOCUMENT;
//	node->right->left = 0;
//	node->right->right = 0;
//
//	search_heredoc(node);
//	return (0);
//}
