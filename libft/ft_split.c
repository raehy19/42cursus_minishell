/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:53:13 by rjeong            #+#    #+#             */
/*   Updated: 2022/07/14 20:58:55 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_word(const char *s, char c)
{
	size_t	i;
	size_t	cnt;

	if (!(*s))
		return (0);
	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			++i;
		if (!(*(s + i)))
			break ;
		++cnt;
		while (*(s + i) && *(s + i) != c)
			++i;
	}
	return (cnt);
}

char	*ft_split_dup(const char *s, char c, size_t *i)
{
	char	*temp;
	int		word_size;

	word_size = 0;
	while (*(s + (*i)) == c)
		++(*i);
	while (*(s + (*i) + word_size) && *(s + (*i) + word_size) != c)
		++word_size;
	temp = (char *) malloc(sizeof(char) * (word_size + 1));
	if (!(temp))
		return (NULL);
	ft_memmove(temp, s + (*i), word_size);
	*(temp + word_size) = '\0';
	(*i) += word_size;
	return (temp);
}

void	*ft_split_mem_free(char **dst, size_t error_i)
{
	size_t	i;

	i = 0;
	while (i < error_i)
	{
		free(*(dst + i));
		*(dst + i) = NULL;
		++i;
	}
	free(dst);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	word_total;
	size_t	word_i;
	size_t	i;

	word_total = ft_count_word(s, c);
	dst = (char **) malloc(sizeof(char *) * (word_total + 1));
	if (!dst)
		return (NULL);
	word_i = 0;
	i = 0;
	while (word_i < word_total)
	{
		*(dst + word_i) = ft_split_dup(s, c, &i);
		if (!(*(dst + word_i)))
			return (ft_split_mem_free(dst, word_i));
		++word_i;
	}
	*(dst + word_total) = NULL;
	return (dst);
}
