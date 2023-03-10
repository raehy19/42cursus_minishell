/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:45 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 20:30:55 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	init_envp(char *envp[])
{
	int				idx;
	int				is_oldpwd;
	t_env			*new;

	idx = 0;
	is_oldpwd = 0;
	while (envp[idx])
	{
		new = make_env(envp[idx]);
		if (g_global.errno != NaE)
			return (1);
		add_env_back(new);
		if (!strcmp(new->name, "OLDPWD"))
			is_oldpwd = 1;
		idx++;
	}
	if (is_oldpwd)
		return (0);
	new = make_env("OLDPWD");
	if (g_global.errno != NaE)
		return (1);
	add_env_back(new);
	return (0);
}
