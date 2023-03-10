/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_rank.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:17 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 14:37:56 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	init_env_order(void)
{
	t_env	*env;

	env = g_global.envp;
	while (env)
	{
		env->order = 0;
		env = env->next;
	}
}

static int	is_large(t_env *largest, t_env *env)
{
	return (!largest || ft_strcmp(env->name, largest->name) > 0);
}

t_env	*get_largest_env(void)
{
	t_env	*env;
	t_env	*largest;

	env = g_global.envp;
	largest = 0;
	while (env)
	{
		if (!env->order && is_large(largest, env))
			largest = env;
		env = env->next;
	}
	return (largest);
}

void	rank_envp(void)
{
	int		size;
	t_env	*env;

	size = get_env_size();
	init_env_order();
	while (size)
	{
		env = get_largest_env();
		env->order = --size;
	}
}
