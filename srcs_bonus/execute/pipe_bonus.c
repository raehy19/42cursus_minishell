/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:45:33 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:11 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

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
