/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fildes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:44:57 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:08 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

int	open_fildes(char *file_name, int oflag, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file_name, oflag);
	if (mode)
		fd = open(file_name, oflag, mode);
	if (fd != -1)
		return (fd);
	g_global.err_num = FAIL_OPEN_FILDES;
	handle_error();
	return (-1);
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
	duplicate_standard_fildes(new_fd);
	if (dup2(exist_fd, new_fd) != -1)
		return ;
	g_global.err_num = FAIL_DUPLICATE_FILDES;
	handle_error();
}

void	init_standard_fildes(void)
{
	if (g_global.standard_fildes[0] != STDIN_FILENO)
	{
		duplicate_fildes(g_global.standard_fildes[0], STDIN_FILENO);
		close_fildes(g_global.standard_fildes[0]);
		g_global.standard_fildes[0] = STDIN_FILENO;
	}
	if (g_global.standard_fildes[1] != STDOUT_FILENO)
	{
		duplicate_fildes(g_global.standard_fildes[1], STDOUT_FILENO);
		close_fildes(g_global.standard_fildes[1]);
		g_global.standard_fildes[1] = STDOUT_FILENO;
	}
}

void	duplicate_standard_fildes(int fd)
{
	if ((fd == STDOUT_FILENO && g_global.standard_fildes[1] == STDOUT_FILENO)
		|| (fd == STDIN_FILENO && g_global.standard_fildes[0] == STDIN_FILENO))
		g_global.standard_fildes[fd] = dup(fd);
	if (g_global.standard_fildes[fd] == -1)
	{
		g_global.err_num = FAIL_DUPLICATE_FILDES;
		handle_error();
	}
}
