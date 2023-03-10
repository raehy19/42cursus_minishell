/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:43:24 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/11 16:10:37 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	open_pipe(int fd[2])
{
	if (pipe(fd) != -1)
		return ;
	g_global.err_num = FAIL_OPEN_PIPE;
	handle_error();
}

void	close_pipe(int pipe[2])
{
	if ((close(pipe[0]) != -1) && (close(pipe[1]) != -1))
		return ;
	g_global.err_num = FAIL_CLOSE_FILDES;
	handle_error();
}

void	close_fildes(int fd)
{
	if (close(fd) != -1)
		return ;
	g_global.err_num = FAIL_CLOSE_FILDES;
	handle_error();
}

void	duplicate_fildes(int exist_fd, int new_fd)
{
	if (dup2(exist_fd, new_fd) != -1)
		return ;
	g_global.err_num = FAIL_DUPLICATE_FILDES;
	handle_error();
}
