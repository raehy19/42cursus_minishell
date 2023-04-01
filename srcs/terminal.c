/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:51:53 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/01 20:21:10 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
