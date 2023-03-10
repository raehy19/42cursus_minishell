/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:43:24 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 17:25:18 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	open_pipe(int fd[2])
{
	int	is_error;

	is_error = (pipe(fd) == -1);
	if (!is_error)
		return ;
	print_error_fildes(FAIL_OPEN_PIPE);
}

void	close_pipe(int pipe[2])
{
	int	is_error;
	
	is_error = ((close(pipe[0]) == -1) || (close(pipe[1]) == -1));
	if (!is_error)
		return ;
	print_error_fildes(FAIL_CLOSE_FILE_DESCRIPTOR);
}

void	close_fildes(int fd)
{
	int	is_error;

	is_error = (close(fd) == -1);
	if (!is_error)
		return ;
	print_error_fildes(FAIL_CLOSE_FILE_DESCRIPTOR);
}

void	duplicate_fildes(int exist_fd, int new_fd)
{
	int	is_error; 

	is_error = (dup2(exist_fd, new_fd) == -1);
	if (!is_error)
		return ;
	print_error_fildes(FAIL_DUPLICATE);
}
