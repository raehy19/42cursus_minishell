/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:32:58 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/19 15:53:48 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

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

void	duplicate_fildes(int exist_fd, int new_fd)
{
	duplicate_standard_fildes(new_fd);
	if (dup2(exist_fd, new_fd) != -1)
		return ;
	g_global.err_num = FAIL_DUPLICATE_FILDES;
	handle_error();
}
