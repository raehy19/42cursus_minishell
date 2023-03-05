/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:18:27 by rjeong            #+#    #+#             */
/*   Updated: 2023/03/05 13:18:30 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*dst;

	dst = (char *) malloc(len + 1);
	if (!dst)
		return (NULL);
	*(dst + len) = '\0';
	return (ft_memmove(dst, s1, len));
}
