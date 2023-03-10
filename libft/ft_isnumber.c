/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeepark <yeepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:23:17 by yeepark           #+#    #+#             */
/*   Updated: 2023/03/10 15:24:33 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *str)
{
	int	idx;

	idx = 0;
	if (*str == '+' || *str == '-')
		idx++;
	if (!str[idx])
		return (0);
	while (ft_isdigit(str[idx]))
		idx++;
	return (!str[idx]);
}
