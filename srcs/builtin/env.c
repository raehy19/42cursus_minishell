/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:29 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 21:07:53 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_env(void)
{
	int		idx;
	t_env	*tmp;

	idx = 0;
	tmp = g_global.envp;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	g_global.exit_status = 0;
	exit(g_global.exit_status);
}

// 마지막 줄 _ 다름 
