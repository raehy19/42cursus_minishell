/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:04:01 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/24 16:04:02 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	handler(int sig, siginfo_t *siginfo, ucontext_t *uap)
{
	(void)uap;
	(void)siginfo;
	if (sig == SIGINT)
	{
		printf("sigint !\n");
	}
	if (sig == SIGQUIT)
	{
		printf("sigquit !\n");
	}
}

void	set_sigaction(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = (void *)handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
