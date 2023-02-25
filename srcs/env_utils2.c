/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:02:18 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 09:50:49 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

t_env	*find_env(t_env **tmp, char *name)
{
	while (*tmp)
	{
		if (!ft_strcmp(name, (*tmp)->name))
			return (*tmp);
		*tmp = (*tmp)->next;
	}
	return (0);
}

void	remove_env(char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_global.envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
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

int	get_env_size(void)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = g_global.envp;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
// 0개일때(=null), segv 안뜨는지 체크
