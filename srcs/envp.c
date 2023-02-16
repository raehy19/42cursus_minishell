/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:45 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 17:19:56 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	init_envp(char *envp[])
{
	int				idx;
	t_env			*new;

	idx = 0;
	while (envp[idx])
	{
		new = make_env(envp[idx]);
		if (g_global.errno != NaE)
			return (1);
		add_env_back(new);
		idx++;
	}
	return (0);
}
