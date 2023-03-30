/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:45:33 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/30 22:50:00 by yeepark          ###   ########.fr       */
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
