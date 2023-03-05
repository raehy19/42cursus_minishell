/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:38 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/05 20:43:59 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

int	is_in(t_redirect_type type)
{
	return (type == REDIRECTING_INPUT || type == HERE_DOCUMENT);
}

int	is_out(t_redirect_type type)
{
	return (type == REDIRECTING_OUTPUT
		|| type == APPENDING_REDIRECTED_OUTPUT);
}

void	handle_in_redirect(t_node *node)
{
	if (node->redirect_type == REDIRECTING_INPUT)
	{
		if (access(node->redirect_filename, F_OK | R_OK) == -1)
		{
			g_global.exit_status = 1;
			print_error_message(node->redirect_filename,
				"No such file or directory");
		}
		node->in_fd = open(node->redirect_filename, O_RDWR);
	}
	dup2(node->in_fd, STDIN_FILENO);
}

void	handle_out_redirect(t_node *node)
{
	int	mode;

	if (node->redirect_type == REDIRECTING_OUTPUT)
		mode = O_RDWR | O_CREAT | O_TRUNC;
	if (node->redirect_type == APPENDING_REDIRECTED_OUTPUT)
		mode = O_RDWR | O_CREAT | O_APPEND;
	node->out_fd = open(node->redirect_filename, mode, 0644);
	dup2(node->out_fd, STDOUT_FILENO);
}

void	handle_redirect(t_node *node)
{
	if (is_in(node->redirect_type))
		handle_in_redirect(node);
	if (is_out(node->redirect_type))
		handle_out_redirect(node);
}
