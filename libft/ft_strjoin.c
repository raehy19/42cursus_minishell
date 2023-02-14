/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:29:13 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/11 15:12:33 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dst)
		return (NULL);
	ft_memmove(dst, s1, s1_len);
	ft_memmove(dst + s1_len, s2, s2_len + 1);
	return (dst);
}
