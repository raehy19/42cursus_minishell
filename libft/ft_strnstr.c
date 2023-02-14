/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:16:55 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/10 20:06:32 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	fi;

	if (!(*(needle)))
		return ((char *) haystack);
	i = 0;
	while ((*(haystack + i)) && i < len)
	{
		fi = 0;
		while ((*(haystack + i + fi) && i + fi < len)
			&& *(haystack + i + fi) == *(needle + fi))
		{
			if (!(*(needle + fi + 1)))
				return ((char *)(haystack + i));
			++fi;
		}
		++i;
	}
	return (NULL);
}
