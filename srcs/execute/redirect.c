/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:58:38 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/30 22:47:44 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	handle_in_redirect(t_node *node)
{
	char	*error_message;

	if (node->redirect_type == REDIRECTING_INPUT)
	{
		if (access(node->redirect_filename, F_OK | R_OK) == -1)
		{
			error_message = "No such file or directory\n";
			g_global.err_num = NO_SUCH_FILE;
			print_redirect_error(node->redirect_filename, error_message);
			return ;
		}
		node->in_fd = open_fildes(node->redirect_filename, O_RDONLY, 0);
	}
	duplicate_fildes(node->in_fd, STDIN_FILENO);
	close_fildes(node->in_fd);
}

void	handle_out_redirect(t_node *node)
{
	int	oflag;

	if (node->redirect_type == REDIRECTING_OUTPUT)
		oflag = O_RDWR | O_CREAT | O_TRUNC;
	if (node->redirect_type == APPENDING_REDIRECTED_OUTPUT)
		oflag = O_RDWR | O_CREAT | O_APPEND;
	node->out_fd = open_fildes(node->redirect_filename, oflag, 0644);
	duplicate_fildes(node->out_fd, STDOUT_FILENO);
	close_fildes(node->out_fd);
}

void	handle_redirect(t_node *node)
{
	int	is_error;

	is_error = 0;
	if (node->redirect_type != HERE_DOCUMENT)
	{
		node->redirect_filename = ft_combine_lump(&node->redirect_linked_str);
		is_error = (handle_redirect_wildcard(node) != 1);
	}
	if (is_error)
		return ;
	if (is_in(node->redirect_type))
		handle_in_redirect(node);
	if (is_out(node->redirect_type))
		handle_out_redirect(node);
}
