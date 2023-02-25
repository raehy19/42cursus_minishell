/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:38 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 19:58:09 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_in(t_redirect_type type)
{
	return (type == REDIRECTING_INPUT || type == HERE_DOCUMENT);
}

int	is_out(t_redirect_type type)
{
	return (type == REDIRECTING_OUTPUT 
		|| type == APPENDING_REDIRECTED_OUTPUT);
}

// in open => access 로 체크 
void	handle_redirect(t_node *node)
{
	int	mode;

	if (node->redirect_type == REDIRECTING_INPUT)
		node->in_fd = open(node->redirect_filename, O_RDWR);
	if (is_in(node->redirect_type))
		dup2(node->in_fd, STDIN_FILENO);
	if (node->redirect_type == REDIRECTING_OUTPUT)
		mode = O_RDWR | O_CREAT | O_TRUNC;
	if (node->redirect_type == APPENDING_REDIRECTED_OUTPUT)
		mode = O_RDWR | O_CREAT | O_APPEND;
	if (is_out(node->redirect_type))
	{
		node->out_fd = open(node->redirect_filename, mode, 0644);
		dup2(node->out_fd, STDOUT_FILENO);
	}
}
