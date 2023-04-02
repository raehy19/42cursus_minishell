/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:02:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/02 13:51:03 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

int	get_env_size(void)
{
	int		size;
	t_env	*env;

	size = 0;
	env = g_global.envp;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
// 0개일때(=null), segv 안뜨는지 체크

t_env	*find_env(char *name)
{
	t_env	*env;

	env = g_global.envp;
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env);
		env = env->next;
	}
	return (0);
}

void	clear_one_env(t_env **env)
{
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = 0;
}

void	remove_env(char *name)
{
	t_env	*env;
	t_env	*prev;

	env = g_global.envp;
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			prev->next = env->next;
			clear_one_env(&env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	clear_env(void)
{
	t_env	*tmp;

	while (g_global.envp)
	{
		tmp = g_global.envp->next;
		clear_one_env(&g_global.envp);
		g_global.envp = tmp;
	}
	return (1);
}
