/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:13:04 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/22 18:29:27 by yeepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dst;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	dst = (char *) malloc(len + 1);
	if (!dst)
		return (NULL);
	return (ft_memmove(dst, s1, len + 1));
}
