/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:45 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/25 10:27:55 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	is_valid_name(char *name)
{
	int	idx;

	if (!name || !(ft_isalpha(*name) || *name == '_'))
		return (0);
	idx = 1;
	while (name[idx])
	{
		if (!(ft_isalnum(name[idx]) || name[idx] == '_'))
			return (0);
		idx++;
	}
	return (1);
}

char	*make_name(char *src, int index)
{
	int		idx;
	char	*des;

	if (index < 1)
		index = ft_strlen(src);
	des = malloc(sizeof(char) * (index + 1));
	if (!des)
		return (0);
	idx = 0;
	while (idx < index)
	{
		des[idx] = src[idx];
		idx++;
	}
	des[idx] = 0;
	return (des);
}

void	set_env(t_env **env, char *src)
{
	int		index;
	t_env	*tmp;

	tmp = *env;
	index = ft_stridx(src, '=');
	tmp->name = make_name(src, index);
	tmp->value = 0;
	if (index > 0)
		tmp->value = ft_substr(src, index + 1, ft_strlen(src));
	if (!tmp->name || (index > 0 && !tmp->value))
		g_global.errno = FAIL_MALLOC;
	if (g_global.errno == NaE)
		tmp->next = 0;
}

t_env	*make_env(char *src)
{
	t_env	*new;

	g_global.errno = NaE;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	set_env(&new, src);
	if (g_global.errno == NaE && !is_valid_name(new->name))
		g_global.errno = INVALID_IDENTIFIER;
	return (new);
}

void	add_env_back(t_env *new)
{
	t_env	*env;

	if (!g_global.envp)
	{
		g_global.envp = new;
		return ;
	}
	env = g_global.envp;
	while (env->next)
		env = env->next;
	env->next = new;
}
