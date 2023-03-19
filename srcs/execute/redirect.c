/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:38 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/19 14:29:09 by yeepark          ###   ########.fr       */
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
			print_redirect_error(node->redirect_filename);
		node->in_fd = open(node->redirect_filename, O_RDWR);
	}
	duplicate_fildes(node->in_fd, STDIN_FILENO);
	close_fildes(node->in_fd);
}

void	handle_out_redirect(t_node *node)
{
	int	mode;

	if (node->redirect_type == REDIRECTING_OUTPUT)
		mode = O_RDWR | O_CREAT | O_TRUNC;
	if (node->redirect_type == APPENDING_REDIRECTED_OUTPUT)
		mode = O_RDWR | O_CREAT | O_APPEND;
	node->out_fd = open(node->redirect_filename, mode, 0644);
	duplicate_fildes(node->out_fd, STDOUT_FILENO);
	close_fildes(node->out_fd);
}

void	handle_redirect(t_node *node)
{
	if (node->redirect_type != HERE_DOCUMENT)
		node->redirect_filename = ft_combine_lump(node->redirect_linked_str);
	if (is_in(node->redirect_type))
		handle_in_redirect(node);
	if (is_out(node->redirect_type))
		handle_out_redirect(node);
}
