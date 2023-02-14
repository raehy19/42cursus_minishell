/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:04:18 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/11 15:12:34 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_c_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s1);
	while (ft_is_c_in_set(*(s1 + i), set) && size > 0)
	{
		++i;
		--size;
	}
	while (ft_is_c_in_set(*(s1 + i + size - 1), set) && size > 0)
		--size;
	dst = (char *) malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	ft_memmove(dst, s1 + i, size);
	*(dst + size) = '\0';
	return (dst);
}
