/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:14:45 by yeepark           #+#    #+#             */
/*   Updated: 2023/02/16 18:16:36 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

int	ft_index(char *str, int c)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			return (idx);
		idx++;
	}
	return (-1);
}

int	is_valid_name(char *str)
{
	int	idx;

	if (!(ft_isalpha(*str) || *str == '_'))
		return (0);
	idx = 1;
	while (str[idx])
	{
		if (!(ft_isalnum(str[idx]) || str[idx] == '_'))
			return (0);
		idx++;
	}
	return (1);
}

t_env	*make_env(char *src)
{
	t_env	*new;
	int		index;

	g_global.errno = NaE;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	index = ft_index(src, '=');
	new->next = 0;
	if (index < 1)
	{
		new->name = ft_strdup(src);
		new->value = 0;
	}
	if (index > 0)
	{
		new->name = ft_substr(src, 0, index);
		new->value = ft_substr(src, index + 1, ft_strlen(src));
	}
	if (!new || !new->name || (index > 0 && !new->value))
		g_global.errno = FAIL_MALLOC;
	if (!is_valid_name(new->name))
		g_global.errno = INVALID_IDENTIFIER;
	return (new);
}

void	add_env_back(t_env *new)
{
	t_env	*tmp;

	tmp = g_global.envp;
	if (!g_global.envp)
	{
		g_global.envp = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
