/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:51:53 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:30 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

extern t_global	g_global;

void	set_control_character(void)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) == -1)
	{
		g_global.err_num = FAIL_GET_TERMIOS;
		handle_error();
		return ;
	}
	terminal.c_lflag |= (ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == -1)
	{
		g_global.err_num = FAIL_SET_TERMIOS;
		handle_error();
	}
}

void	unset_control_character(void)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) == -1)
	{
		g_global.err_num = FAIL_GET_TERMIOS;
		handle_error();
		return ;
	}
	terminal.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == -1)
	{
		g_global.err_num = FAIL_SET_TERMIOS;
		handle_error();
	}
}
