/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:50:42 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/07 21:56:35 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (dst > src)
	{
		i = len - 1;
		while (i > -1)
		{
			*(((unsigned char *) dst) + i) = *(((unsigned char *) src) + i);
			--i;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
