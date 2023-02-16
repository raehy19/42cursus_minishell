/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:01:00 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 19:31:36 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern t_global	g_global;

void	init_rank(void)
{
	t_env	*tmp;

	tmp = g_global.envp;
	while (tmp)
	{
		tmp->order = 0;
		tmp = tmp->next;
	}
}

int	get_envp_size(void)
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

int	is_large(t_env *largest, t_env *tmp)
{
	return (!largest || (largest && ft_strcmp(tmp->name, largest->name) > 0));
}

t_env	*get_largest_env(void)
{
	int		idx;
	t_env	*tmp;
	t_env	*largest;

	idx = 0;
	tmp = g_global.envp;
	largest = 0;
	while (tmp)
	{
		if (!tmp->order && is_large(largest, tmp))
			largest = tmp;
		tmp = tmp->next;
	}
	return (largest);
}

void	rank_envp(void)
{
	int		size;
	t_env	*env;

	size = get_envp_size();
	init_rank();
	while (size)
	{
		env = get_largest_env();
		env->order = --size;
	}
}
