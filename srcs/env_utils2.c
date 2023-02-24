/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:02:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/24 21:30:25 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

t_env	*find_env(char *name)
{
	t_env	*tmp;

	tmp = g_global.envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	remove_env(char *name)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*removed;

	tmp = g_global.envp;
	removed = find_env(name);
	while (tmp)
	{
		if (removed == tmp)
		{
			prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
