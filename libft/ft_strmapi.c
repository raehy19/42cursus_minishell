/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:25:38 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/11 16:35:56 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	dst = (char *) malloc (sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(dst + i) = f(i, *(s + i));
		++i;
	}
	*(dst + size) = '\0';
	return (dst);
}
