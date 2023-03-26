/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:51:53 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/26 18:52:36 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_control_character(void)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

void	unset_comtrol_character(void)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}
