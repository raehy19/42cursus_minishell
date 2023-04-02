/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:45:59 by yeepark           #+#    #+#             */
/*   Updated: 2023/04/01 21:22:06 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

extern t_global	g_global;

int	get_size(char **array, int size)
{
	int	cnt;
	int	idx;

	cnt = 0;
	idx = 0;
	while (idx < size)
	{
		if (array[idx])
			cnt++;
		idx++;
	}
	return (cnt);
}

char	**make_two_dim(char	**array, int size)
{
	int		idx;
	int		new_idx;
	char	**new_array;

	idx = 0;
	new_idx = 0;
	if (size == 1 && !ft_strcmp(array[0], ""))
		return (array);
	new_array = malloc(sizeof(char *) * (get_size(array, size) + 1));
	if (!new_array)
	{
		g_global.err_num = FAIL_MALLOC;
		handle_error();
	}
	while (idx < size)
	{
		if (array[idx])
			new_array[new_idx++] = array[idx];
		idx++;
	}
	new_array[new_idx] = 0;
	free(array);
	return (new_array);
}
