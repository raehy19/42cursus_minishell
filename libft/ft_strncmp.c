/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:25:14 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/10 17:20:20 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)(*(s1 + i)) != (unsigned char)(*(s2 + i))
			|| !(*(s1 + i)) || !(*(s2 + i)))
			return ((int)((unsigned char)(*(s1 + i))
				- (unsigned char)(*(s2 + i))));
		++i;
	}
	return (0);
}
