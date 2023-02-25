/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:29 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 13:39:07 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	ft_env(void)
{
	int		idx;
	t_env	*env;

	idx = 0;
	env = g_global.envp;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	g_global.exit_status = 0;
	exit(g_global.exit_status);
}

// 마지막 줄 _ 다름 
