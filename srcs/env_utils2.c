/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:02:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 10:28:37 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_env	*find_env(t_env **env, char *name)
{
	while (*env)
	{
		if (!ft_strcmp(name, (*env)->name))
			return (*env);
		*env = (*env)->next;
	}
	return (0);
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
			free(env->name);
			free(env->value);
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
		free(g_global.envp->name);
		free(g_global.envp->value);
		free(g_global.envp);
		g_global.envp = tmp;
	}
	return (1);
}
