/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:20:56 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/09 21:35:10 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	c;
	size_t			i;

	c = (unsigned char) value;
	i = 0;
	while (i < num)
	{
		*(((unsigned char *)ptr) + i) = c;
		++i;
	}
	return (ptr);
}
